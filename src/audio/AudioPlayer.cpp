#include "AudioPlayer.h"

AudioPlayer::AudioPlayer() {
    initialize();
}

void AudioPlayer::initialize() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        Dialog::show_error_message("Audio library could not be initialized...");
    }
}

void AudioPlayer::audio_callback(void *user_data, Uint8 *stream, int length) {
    AudioData * audio = (AudioData *) user_data;

    // get the current playback duration in bytes
    Uint32 bytes_played = audio->length - audio->samples * audio->channels * SDL_AUDIO_BITSIZE(audio->format) / 8;
    // update the playback duration in bytes
    global::AUDIO_POSITION = global::AUDIO_SIZE - bytes_played;

    Uint32 window_size = audio->samples;

    // input and output vectors for the FFT algorithm
    fftw_complex * fft_input = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * window_size);
    fftw_complex * fft_output = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * window_size);
    fftw_plan fft_plan = fftw_plan_dft_1d(window_size, fft_input, fft_output, FFTW_FORWARD, FFTW_ESTIMATE);

    copy_stream_to_fft_input(fft_input, audio);
    fftw_execute(fft_plan);

    std::pair<size_t, size_t> bin_range = frequency_range_to_bin_indexes(global::LOW_FREQUENCY, global::HIGH_FREQUENCY, audio);
    size_t start_bin = bin_range.first;
    size_t end_bin = bin_range.second;

    int num_bins = end_bin - start_bin;

    // calculate the decibel volume of each frequency bin
    double * db_values = new double[num_bins];
    for (int i = start_bin; i < end_bin; i++) {
        int index = i - start_bin;

        double real_part = fft_output[i][0];
        double imag_part = fft_output[i][1];

        double magnitude = sqrt(real_part * real_part + imag_part * imag_part);
        double db_value = magnitude_to_db(magnitude);

        db_values[index] = db_value;
    }

    int num_chunks = global::NUM_CHUNKS;
    int chunk_width = num_bins / num_chunks;

    // average the frequency bins for visualisation
    for (int i = 0; i < num_chunks; i++) {
        double db_sum = 0;

        for (int j = 0; j < chunk_width; j++) {
            int index = i * chunk_width + j;
            db_sum += db_values[index];
        }

        double chunk_db = db_sum / chunk_width;
        global::SPECTRUM[i] = chunk_db;
    }

    free_fftw_data(fft_input, fft_output, fft_plan);
    copy_to_stream_and_advance(stream, audio, length);
}

void AudioPlayer::load_audio(const std::string &filename) {
    // close audio if it was already playing
    SDL_CloseAudio();

    SDL_AudioSpec wav_spec;
    Uint32 wav_length;
    Uint8 * wav_buffer;

    // load audio file
    if (SDL_LoadWAV(filename.c_str(), &wav_spec, &wav_buffer, &wav_length) == NULL) {
        Dialog::show_error_message("Cannot load the provided audio file...");
    }

    // fill the AudioData struct with audio data
    audio.position = wav_buffer;
    audio.length = wav_length;
    audio.sample_rate = wav_spec.freq;
    audio.channels = wav_spec.channels;
    audio.samples = wav_spec.samples;
    audio.format = wav_spec.format;

    // set the callback function
    wav_spec.callback = &AudioPlayer::audio_callback;
    wav_spec.userdata = &audio;

    // store the overall audio size
    global::AUDIO_SIZE = wav_length;

    // open the audio file
    if (SDL_OpenAudio(&wav_spec, NULL) < 0) {
        Dialog::show_error_message("Cannot open the provided audio file...");
    }
}

void AudioPlayer::play_audio() {
    // start playing audio in a separate thread
    audio_thread = std::thread(&AudioPlayer::audio_playback, this);
    audio_thread.detach();
}

void AudioPlayer::resume_audio() {
    SDL_PauseAudio(0);
}

void AudioPlayer::pause_audio() {
    SDL_PauseAudio(1);
}

void AudioPlayer::audio_playback() {
    SDL_PauseAudio(0);

    // play audio as long as there is data to be played
    while (audio.length > 0) {
        SDL_Delay(1);
    }

    // close and free audio data
    SDL_CloseAudio();
    SDL_FreeWAV(audio.position);
}

void AudioPlayer::load_volume_levels() {
    global::VOLUME_LEVELS = get_volume_levels(audio);
    global::MAX_VOLUME = *std::max_element(global::VOLUME_LEVELS.begin(), global::VOLUME_LEVELS.end());
}