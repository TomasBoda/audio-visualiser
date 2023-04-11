#ifndef FFT_MUSIC_VISUALISER_AUDIOUTIL_H
#define FFT_MUSIC_VISUALISER_AUDIOUTIL_H

#include <SDL.h>
#include <fftw3.h>
#include <utility>
#include <vector>

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

/*
 * Copy audio data back to stream
 * This method copies the processed audio data back to stream and moves the audio stream pointer
 * @param stream audio stream data
 * @param audio audio data @see AudioData
 * @param length size of the current audio chunk
 */
void copy_to_stream_and_advance(Uint8 * & stream, AudioData * & audio, int length);

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
void copy_stream_to_fft_input(fftw_complex * & fft_input, AudioData * & audio);

/*
 * Convert frequency range in Hz to FFT bin range
 * This method converts the desired frequency range into a FFT bin range
 * @param low_frequency lower frequency bound in Hz
 * @param high_frequency upper frequency bound in Hz
 * @param audio audio data @see AudioData
 * @return pair of lower and upper FFT bin bounds
 */
std::pair<size_t, size_t> frequency_range_to_bin_indexes(int low_frequency, int high_frequency, AudioData * & audio);

/*
 * Get decibel levels of audio file by seconds
 * This method calculates the highest decibel level of each second of the audio file
 * @return vector of decibel levels
 */
std::vector<double> & get_volume_levels(AudioData & audio);

/*
 * Convert frequency magnitude to decibel value
 * This method converts a frequency magnitude to the corresponding decibel value
 * @param magnitude frequency magnitude
 * @return decibel value
 */
double magnitude_to_db(double magnitude);

#endif
