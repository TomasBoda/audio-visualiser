#include "Observer.h"

void Observer::play(const std::string &filename) {
    audio_player->load_audio(filename);
    audio_player->load_volume_levels();
    audio_player->play_audio();
}

void Observer::resume() {
    audio_player->resume_audio();
}

void Observer::pause() {
    audio_player->pause_audio();
}