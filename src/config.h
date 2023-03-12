#include <mutex>

namespace global {
    extern int WIDTH;
    extern int HEIGHT;

    extern const char * FILENAME;

    extern int NUM_CHUNKS;
    extern double SPECTRUM[60];
    extern std::mutex MUTEX;
}