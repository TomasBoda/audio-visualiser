#include <mutex>

namespace global {
    extern int WIDTH;
    extern int HEIGHT;
    extern const char * APP_NAME;

    extern const char * FILENAME;

    extern std::mutex MUTEX;
    extern const int NUM_CHUNKS;
    extern double SPECTRUM[180];
    extern int SMOOTHING_FACTOR;
    extern double GRAVITY;
}