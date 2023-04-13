#include <mutex>
#include "config.h"

namespace global {
    int WIDTH = 1800;
    int HEIGHT = 1000;

    const char * FILENAME = "../src/assets/bilderbuch-bungalow.wav";

    std::mutex MUTEX;

    const int NUM_CHUNKS = 360;

    double * SPECTRUM_LEFT = new double[NUM_CHUNKS];
    double * SPECTRUM_RIGHT = new double[NUM_CHUNKS];

    int LOW_FREQUENCY = 0;
    int HIGH_FREQUENCY = 20000;

    std::vector<double> VOLUME_LEVELS;
    double MAX_VOLUME = 0;

    int AUDIO_SIZE = 0;
    int AUDIO_POSITION = 0;
}