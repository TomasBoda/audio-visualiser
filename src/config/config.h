#include <wx/wx.h>
#include <mutex>
#include <vector>

using Graphics = wxDC &;
using Event = wxCommandEvent &;

namespace global {
    extern int WIDTH;
    extern int HEIGHT;

    extern const char * FILENAME;

    extern std::mutex MUTEX;

    extern int LOW_FREQUENCY;
    extern int HIGH_FREQUENCY;

    extern const int NUM_CHUNKS;
    extern double * SPECTRUM;

    extern int SMOOTHING_FACTOR;
    extern double GRAVITY;

    extern std::vector<double> VOLUME_LEVELS;
    extern double MAX_VOLUME;

    extern int AUDIO_SIZE;
    extern int AUDIO_POSITION;
}