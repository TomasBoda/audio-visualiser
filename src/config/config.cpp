#include <mutex>
#include "config.h"

namespace global {
    int WIDTH = 1800;
    int HEIGHT = 1000;

    const char * FILENAME = "../src/assets/bilderbuch-bungalow.wav";

    std::mutex MUTEX;

    const int NUM_CHUNKS = 360;
    double * SPECTRUM = new double[NUM_CHUNKS];

    int LOW_FREQUENCY = 0;
    int HIGH_FREQUENCY = 20000;

    int SMOOTHING_FACTOR = 20;
    double GRAVITY = 3;

    std::vector<double> VOLUME_LEVELS;
    double MAX_VOLUME = 0;

    int AUDIO_SIZE = 0;
    int AUDIO_POSITION = 0;
}