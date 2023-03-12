#include <mutex>
#include "config.h"

using namespace std;

namespace global {
    int WIDTH = 1200;
    int HEIGHT = 700;

    const char * FILENAME = "../never-gonna-give-u-up.wav";
    //const char * FILENAME = "../drums.wav";

    int NUM_CHUNKS = 60;
    double SPECTRUM[60] = {};
    mutex MUTEX;
}