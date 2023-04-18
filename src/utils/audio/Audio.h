#ifndef FFT_MUSIC_VISUALISER_AUDIOUTIL_H
#define FFT_MUSIC_VISUALISER_AUDIOUTIL_H

#include <SDL.h>
#include <fftw3.h>
#include <utility>
#include <vector>
#include <memory>
#include "../../config/config.h"

/*
 * Audio data container
 * This struct stores audio wave file data
 */
struct AudioData {
    Uint8 * position;
    Uint32 length;
    Uint32 sample_rate;
    Uint32 channels;
    Uint32 samples;
    SDL_AudioFormat format;
};

using audio_ptr = std::shared_ptr<AudioData>;

/*
 * Copy audio data back to stream
 * This method copies the processed audio data back to stream and moves the audio stream pointer
 * @param stream audio stream data
 * @param audio audio data @see AudioData
 * @param length size of the current audio chunk
 */
void copy_to_stream_and_advance(Uint8 * & stream, audio_ptr audio, int length);

/*
 * Free FFT vectors after processing
 * This method frees the data used in FFT after the data has been processed
 * @param fft_input input vector of the FFT algorithm
 * @param fft_output output vector of the FFT algorithm
 * @param fft_plan FFT struct holding the input and output vectors of the FFT algorithm
 */
void free_fftw_data(fftw_complex * & fft_input, fftw_complex * & fft_output, fftw_plan & fft_plan);

/*
 * Copy audio data to the FFT input vector
 * This method copies the audio data to the FFT input vector
 * @param fft_input input vector of the FFT algorithm
 * @param audio audio data @see AudioData
 */
void copy_stream_to_fft_input(fftw_complex * & fft_input, audio_ptr audio, int channel);

/*
 * Calculate frequency spectrum
 * This method calculates the frequency spectrum using the FFT algorithm and stores its decibel magnitudes in global spectrum variables
 * @param audio AudioData of the stream
 * @param window_size size of the FFT window
 * @param channel channel to be calculated
 * @param frequency_spectrum variable where the decibel values of the frequency spectrum should be stored
 */
void calculate_fft_frequency_spectrum(audio_ptr audio, Uint32 window_size, int channel, double_array & frequency_spectrum);

/*
 * Convert frequency range in Hz to FFT bin range
 * This method converts the desired frequency range into a FFT bin range
 * @param low_frequency lower frequency bound in Hz
 * @param high_frequency upper frequency bound in Hz
 * @param audio audio data @see AudioData
 * @return pair of lower and upper FFT bin bounds
 */
std::pair<size_t, size_t> frequency_range_to_bin_indexes(int low_frequency, int high_frequency, audio_ptr audio);

/*
 * Get decibel levels of audio file by seconds
 * This method calculates the highest decibel level of each second of the audio file
 * @return vector of decibel levels
 */
std::vector<double> get_volume_levels(audio_ptr audio);

void update_audio_position(audio_ptr audio);

/*
 * Convert frequency magnitude to decibel value
 * This method converts a frequency magnitude to the corresponding decibel value
 * @param magnitude frequency magnitude
 * @return decibel value
 */
double magnitude_to_db(double magnitude);

#endif
