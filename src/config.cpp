#include <mutex>
#include "config.h"

using namespace std;

namespace global {
    int WIDTH = 800;
    int HEIGHT = 500;

    const char * FILENAME = "../never-gonna-give-u-up.wav";

    int NUM_CHUNKS = 64;
    double SPECTRUM[64] = {};
    mutex MUTEX;
}