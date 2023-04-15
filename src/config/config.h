#include <wx/wx.h>
#include <fftw3.h>
#include <mutex>
#include <vector>
#include <memory>
#include "../utils/audio/Audio.h"

using Graphics = wxDC &;
using Event = wxCommandEvent &;

template<typename T>
using array_ptr = std::unique_ptr<T[]>;

using double_array = array_ptr<double>;
using double_vector = std::vector<double>;

namespace global {
    extern int WIDTH;
    extern int HEIGHT;

    extern const char * FILENAME;

    extern std::mutex MUTEX;

    extern int LOW_FREQUENCY;
    extern int HIGH_FREQUENCY;

    extern const int NUM_CHUNKS;

    extern double_array SPECTRUM_LEFT;
    extern double_array SPECTRUM_RIGHT;

    extern std::vector<double> VOLUME_LEVELS;
    extern double MAX_VOLUME;

    extern int AUDIO_SIZE;
    extern int AUDIO_POSITION;
}