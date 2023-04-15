#include "config.h"

namespace global {
    int WIDTH = 1800;
    int HEIGHT = 1000;

    const char * FILENAME = "../src/assets/tonight-you-are-mine.wav";

    std::mutex MUTEX;

    const int NUM_CHUNKS = 360;
    double_array SPECTRUM_LEFT = std::make_unique<double[]>(NUM_CHUNKS);
    double_array SPECTRUM_RIGHT = std::make_unique<double[]>(NUM_CHUNKS);

    int LOW_FREQUENCY = 0;
    int HIGH_FREQUENCY = 20000;

    double_vector VOLUME_LEVELS;
    double MAX_VOLUME = 0;

    int AUDIO_SIZE = 0;
    int AUDIO_POSITION = 0;
}