#include "AudioPlayer.h"

AudioPlayer::AudioPlayer() {
    initialize();
    audio = std::make_shared<AudioData>();
}

void AudioPlayer::initialize() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        Dialog::show_error_message("Audio library could not be initialized...");
    }
}

void AudioPlayer::audio_callback(void * user_data, Uint8 * stream, int length) {
    audio_ptr audio = std::static_pointer_cast<AudioData>(*(static_cast<std::shared_ptr<void>*>(user_data)));

    // update the audio remaining time
    update_audio_position(audio);

    Uint32 window_size = audio->samples;

    // calculate the frequency spectrum of each channel using the FFT algorithm
    if (audio->channels == 1) {
        calculate_fft_frequency_spectrum(audio, window_size, 0, global::SPECTRUM_LEFT);
        calculate_fft_frequency_spectrum(audio, window_size, 0, global::SPECTRUM_RIGHT);
    } else {
        calculate_fft_frequency_spectrum(audio, window_size, 0, global::SPECTRUM_LEFT);
        calculate_fft_frequency_spectrum(audio, window_size, 1, global::SPECTRUM_RIGHT);
    }

    // copy audio data back to stream and move the audio pointer to next chunk
    copy_to_stream_and_advance(stream, audio, length);
}

void AudioPlayer::load_audio(const std::string & filename) {
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
    audio->position = wav_buffer;
    audio->length = wav_length;
    audio->sample_rate = wav_spec.freq;
    audio->channels = wav_spec.channels;
    audio->samples = wav_spec.samples;
    audio->format = wav_spec.format;

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
    while (global::AUDIO_POSITION < global::AUDIO_SIZE) {
        SDL_Delay(1);
    }

    // close audio
    SDL_CloseAudio();
}

void AudioPlayer::load_volume_levels() {
    global::VOLUME_LEVELS = get_volume_levels(audio);
    global::MAX_VOLUME = *std::max_element(global::VOLUME_LEVELS.begin(), global::VOLUME_LEVELS.end());
}