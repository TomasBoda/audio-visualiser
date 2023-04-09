#include <mutex>
#include "config.h"

namespace global {
    int WIDTH = 1800;
    int HEIGHT = 1000;

    const char * FILENAME = "../src/assets/bilderbuch-bungalow.wav";

    std::mutex MUTEX;
    const int NUM_CHUNKS = 360;
    double * SPECTRUM = new double[NUM_CHUNKS];
    int SMOOTHING_FACTOR = 20;
    double GRAVITY = 3;
}