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