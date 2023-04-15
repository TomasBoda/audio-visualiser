#include "Audio.h"

void copy_to_stream_and_advance(Uint8 * & stream, AudioData * & audio, int length) {
    SDL_memcpy(stream, audio->position, length);
    audio->position += length;
    audio->length -= length;
}

void free_fftw_data(fftw_complex * & fft_input, fftw_complex * & fft_output, fftw_plan & fft_plan) {
    fftw_destroy_plan(fft_plan);
    fftw_free(fft_input);
    fftw_free(fft_output);
}

void copy_stream_to_fft_input(fftw_complex * & fft_input, AudioData * & audio, int channel) {
    Uint32 window_size = audio->samples;

    for (int i = 0; i < window_size; i++) {
        Sint16 * audio_data = (Sint16*) audio->position;
        fft_input[i][0] = (double) audio_data[i * audio->channels + channel] / 32768.0;
        fft_input[i][1] = 0.0;
    }
}

void calculate_fft_frequency_spectrum(AudioData * & audio, Uint32 window_size, int channel, double_array & frequency_spectrum) {
    fftw_complex * fft_input = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * window_size);
    fftw_complex * fft_output = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * window_size);
    fftw_plan fft_plan = fftw_plan_dft_1d(window_size, fft_input, fft_output, FFTW_FORWARD, FFTW_ESTIMATE);

    copy_stream_to_fft_input(fft_input, audio, channel);
    fftw_execute(fft_plan);

    std::pair<size_t, size_t> bin_range = frequency_range_to_bin_indexes(global::LOW_FREQUENCY, global::HIGH_FREQUENCY, audio);
    size_t start_bin = bin_range.first;
    size_t end_bin = bin_range.second;

    int num_bins = end_bin - start_bin;

    // calculate the decibel volume of each frequency bin
    double_array db_values = std::make_unique<double[]>(num_bins);
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
        frequency_spectrum[i] = chunk_db;
    }

    free_fftw_data(fft_input, fft_output, fft_plan);
}

std::pair<size_t, size_t> frequency_range_to_bin_indexes(int low_frequency, int high_frequency, AudioData * & audio) {
    int window_size = audio->samples;
    int num_bins = window_size / 2 + 1;
    Uint32 sample_rate = audio->sample_rate;

    std::pair<size_t, size_t> indexes;

    for (int i = 0; i < num_bins - 1; i++) {
        double hz1 = i * sample_rate / window_size;
        double hz2 = (i + 1) * sample_rate / window_size;

        if (hz1 < low_frequency && hz2 >= low_frequency) {
            indexes.first = i + 1;
        }

        if (hz1 <= high_frequency && hz2 > high_frequency) {
            indexes.second = i;
            break;
        }
    }

    return indexes;
}

std::vector<double> & get_volume_levels(AudioData & audio) {
    std::vector<double> * levels = new std::vector<double>;

    int samples_per_second = audio.sample_rate;
    int bytes_per_second = samples_per_second * (SDL_AUDIO_BITSIZE(audio.format) / 8) * audio.channels;
    int num_seconds = (int) (audio.length / bytes_per_second);

    for (int i = 0; i < num_seconds; i++) {
        int start_byte = i * bytes_per_second;
        Uint8 * chunk = audio.position + start_byte;

        int num_samples = bytes_per_second / sizeof(Sint16);
        float sum_squares = 0.0f;

        for (int i = 0; i < num_samples; i++) {
            Sint16 sample = ((Sint16*) chunk)[i];
            float sample_to_float = (float) sample / 32768.0f;
            sum_squares += sample_to_float * sample_to_float;
        }

        float root_mean_square = sqrtf(sum_squares / num_samples);
        levels->push_back(root_mean_square);
    }

    return *levels;
}

void update_audio_position(AudioData * & audio) {
    // get the current playback duration in bytes
    Uint32 bytes_played = audio->length - audio->samples * audio->channels * SDL_AUDIO_BITSIZE(audio->format) / 8;
    // update the playback duration in bytes
    global::AUDIO_POSITION = global::AUDIO_SIZE - bytes_played;
}

double magnitude_to_db(double magnitude) {
    return 20 * log10(magnitude);
}