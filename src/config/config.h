#include <mutex>
#include <wx/wx.h>

using Graphics = wxDC &;
using Event = wxCommandEvent &;

namespace global {
    extern int WIDTH;
    extern int HEIGHT;

    extern const char * FILENAME;

    extern std::mutex MUTEX;
    extern const int NUM_CHUNKS;
    extern double * SPECTRUM;
    extern int SMOOTHING_FACTOR;
    extern double GRAVITY;
}