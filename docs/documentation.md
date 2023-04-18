# Documentation
This document serves as documentation to the Music Visualiser source code.

## Tools and Dependencies
The application is written in `C++` using the `CMake` build tool and utilizes the following external libraries.
- [wxWidgets](https://github.com/wxWidgets/wxWidgets) - used for cross-platform window and GUI
- [SDL2](https://github.com/libsdl-org/SDL/tree/SDL2) - used for audio processing and playback
- [FFTW3](https://github.com/FFTW/fftw3) - used for Fast Fourier Transform calculations

These libraries are added to the project as submodules and are built from source using `CMakeLists.txt`.

## Main Components
The two most important components are the [AudioPlayer](../src/audio/AudioPlayer.h) and the [Visualiser](../src/utils/visualiser/Visualiser.h) classes.

### Audio Player
The [AudioPlayer](../src/audio/AudioPlayer.h) class is responsible for processing audio files and their data. It can load an audio file, start it in a new thread and control its playback.

It utilizes the `AudioData` struct defined in [Audio](../src/utils/audio/Audio.h) util that represents an audio object with all its necessary data.
```c++
struct AudioData {
    Uint8 * position;
    Uint32 length;
    Uint32 sample_rate;
    Uint32 channels;
    Uint32 samples;
    SDL_AudioFormat format;
};
```

This object is then passed to the `SDL2` and is used in the `audio_callback` function that processes current audio playback and its data in real time.

The `audio_callback` function is responsible for calculating the frequency spectrum of each audio chunk (current audio data) and saving it to a global variable for visualisation.
```c++
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
```

### Calculating the Frequency Spectrum
The `audio_callback` function uses the `calculate_fft_frequency_spectrum` function defined in the [Audio](../src/utils/audio/Audio.h) util that calculates the frequency spectrum using the Fast Fourier Transform (FFT) algorithm.

The calculation of the frequency spectrum works as follows.

First, we allocate the FFT input and output vectors and create a FFT plan object that is used as the input to the FFT algorithm.
```c++
fftw_complex * fft_input = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * window_size);
fftw_complex * fft_output = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * window_size);
fftw_plan fft_plan = fftw_plan_dft_1d(window_size, fft_input, fft_output, FFTW_FORWARD, FFTW_ESTIMATE);
```
Then, we copy the current audio chunk to the FFT input vector.
```c++
Uint32 window_size = audio->samples;

for (int i = 0; i < window_size; i++) {
    Sint16 * audio_data = (Sint16*) audio->position;
    fft_input[i][0] = (double) audio_data[i * audio->channels + channel] / 32768.0;
    fft_input[i][1] = 0.0;
}
```
With the input vector holding the current audio data, we perform the FFT algorithm on the `fft_plan` using `fftw_execute(fft_plan);`.

Next, we loop through the FFT output vector, which now holds the transformed values (frequency bins) and calculate the magnitude of each frequency bin.
```c++
double real_part = fft_output[i][0];
double imag_part = fft_output[i][1];

double magnitude = sqrt(real_part * real_part + imag_part * imag_part);
```
Finally, we convert each frequency magnitude to a decibel value using the following formula.
```c++
double magnitude_to_db(double magnitude) {
    return 20 * log10(magnitude);
}
```
We store the decibel value of each frequency bin in an array and assign the result to a global variable that is used to visualise the frequency spectrum.

### Visualiser
The [Visualiser](../src/utils/visualiser/Visualiser.h) is an abstract class that can visualize the frequency spectrum and perform operations on it. It holds the frequency spectrum data and consists of four virtual methods used to implement initialization, update and render of the visualisation.

#### Equalizer Visualiser
The [Equalizer](../src/gui/visualisers/equalizer/Equalizer.h) visualiser plots a two-dimensional visualisation of the decibel magnitudes (vertical axis) of the frequency bins (horizontal axis).

There is one important thing about the plotting that is non-trivial, which is that the frequency bins are not distributed equally among the horizontal axis. 
That is because in a relatively normal wave file, the lower frequencies are usually much louder than the higher frequencies, which results in not so aesthetic visualisation. 
Therefore, I opted for specifying frequency ranges and their corresponding widths in pixels, which results in a much aesthetically pleasing visualisation.

For this to work, I needed to create helper arrays with the delimiters, widths and frequency bin indexes.
```c++
using double_vector = std::vector<double>

double_vector delimiters = double_vector{ 0, 200, 1000, 8000, 20000};

double_vector indexes = double_vector{ 0,
    global::NUM_CHUNKS / (hz_range / (delimiters[1] - delimiters[0])),
    global::NUM_CHUNKS / (hz_range / (delimiters[2] - delimiters[1])),
    global::NUM_CHUNKS / (hz_range / (delimiters[3] - delimiters[2])),
    global::NUM_CHUNKS / (hz_range / (delimiters[4] - delimiters[3])) };

double_vector widths = double_vector{
    global::WIDTH / 10.0 * 2.0,
    global::WIDTH / 10.0 * 2.0,
    global::WIDTH / 10.0 * 3.0,
    global::WIDTH / 10.0 * 3.0
};
```

- the `delimiters` array represents the individual frequency ranges we want to distinguish
- the `indexes` array represents the start and end index of the frequency bins of each frequency range in the `delimiters` array
- the `widths` array represents the widths of the frequency ranges in pixels

With these three support arrays, we can plot the frequency spectrum as follows.

First, we loop through the number of frequency ranges and calculate the `x` offset using the `widths` array.
```c++
for (int i = 0; i < num_of_parts; i++) {
    double offset = 0;
    for (int j = 0; j < i; j++) offset += widths[j];

    // ...
}
```
Then, we loop through the frequency bins in the current range using the `indexes` array, calculate the `x`, `y`, `width` and `height` of the current frequency bin and plot it.
```c++
// ...

for (int j = indexes[i]; j < indexes[i + 1]; j++) {
    double height = frequency_spectrum[j];
    double width = widths[i] / (indexes[i + 1] - indexes[i]);

    int x = offset + (j - indexes[i]) * width;
    int y = global::HEIGHT - height;
    
    draw_frequency_line(graphics, x_prev, y_prev, x, y, colour);
}

// ...
```
Finally, we store the previous `x` and `y` coordinates to helper values for the next iteration.
```c++
x_prev = x;
y_prev = y;
```

This purpose of this whole process is to make the lower frequencies take up more horizontal space in the window, so the frequency spectrum plot looks less rugged.

#### Circular Visualiser
The [Circular](../src/gui/visualisers/circular/Circular.h) visualiser plots the frequency spectrum around a central circle. It uses basic geometric operations to calculate the `x` and `y` coordinates of each frequency bin based on the angle and magnitude of the frequency bin.

There is one important thing about the plotting that is non-trivial, which is averaging adjacent frequency bins, so that the whole animation is smoother and less spiky. For this, I created a helper variable `smoothing_factor`, which is an integer value representing the number of adjacent frequency bins to be averaged. The greater the number is, the more smooth the visualisation is.

Averaging the frequency bins is calculated in each tick of the visualisation and works as follows.

Firstly, we loop through all frequency bins in our spectrum.
```c++
for (int i = 0; i < global::NUM_CHUNKS * 2; i++) {
    double new_frequency = 0;
    
    // ...
}
```
Then, we loop through adjacent frequency bins using the `smoothing_factor` variable and calculate the real frequency bin index.
```c++
for (int j = 0; j < smoothing_factor; j++) {
    const int index = (i + j) % (global::NUM_CHUNKS * 2);
    const int index_reversed = global::NUM_CHUNKS - (index % global::NUM_CHUNKS) - 1;

    // ...
}
```
Next, we check whether we are dealing with the left or right channel and update the `new_frequency` accordingly.
```c++
if (index < global::NUM_CHUNKS) {
    new_frequency += normalize_frequency(global::SPECTRUM_LEFT[index]);
} else {
    new_frequency += normalize_frequency(global::SPECTRUM_RIGHT[index_reversed]);
}
```
Finally, we average the `new_frequency` by dividing it by `smoothing_factor` and update the frequency spectrum.
```c++
new_frequency /= smoothing_factor;

if (new_frequency > frequency_spectrum[i]) {
    frequency_spectrum[i] = new_frequency;
}
```
This ensures that each frequency bin is averaged with its adjacent frequency bins, which makes the frequency plot smoother and much more aesthetically pleasing.

#### Volumes Visualiser
The [Volumes](../src/gui/visualisers/volumes/Volumes.h) visualiser plots the volume levels of each second of the audio file, resulting in a waveform structure.

To calculate the number of seconds and the maximum volume of the audio in each second, we need to perform the following operations.

Firstly, we determine the bytes per each second and the total number of seconds of the audio file.
```c++
int samples_per_second = audio->sample_rate;
int bytes_per_second = samples_per_second * (SDL_AUDIO_BITSIZE(audio->format) / 8) * audio->channels;
int num_seconds = (int) (audio->length / bytes_per_second);
```
Then, we loop through each second and calculate the root mean square, which represents the overall volume.
```c++
for (int i = 0; i < num_seconds; i++) {
    int start_byte = i * bytes_per_second;
    Uint8 * chunk = audio->position + start_byte;

    int num_samples = bytes_per_second / sizeof(Sint16);
    float sum_squares = 0.0f;

    for (int i = 0; i < num_samples; i++) {
        Sint16 sample = ((Sint16*) chunk)[i];
        float sample_to_float = (float) sample / 32768.0f;
        sum_squares += sample_to_float * sample_to_float;
    }

    float root_mean_square = sqrtf(sum_squares / num_samples);
}
```
Finally, we store this value into an array and use this array to plot the audio waveform.