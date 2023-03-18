#include <mutex>
#include "config.h"

using namespace std;

namespace global {
    int WIDTH = 1200;
    int HEIGHT = 700;

    //const char * FILENAME = "../never-gonna-give-u-up.wav";
    const char * FILENAME = "../malby.wav";

    int NUM_CHUNKS = 120;
    double SPECTRUM[120] = {};
    mutex MUTEX;
}