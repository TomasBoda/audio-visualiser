#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2_mixer/SDL_mixer.h>

#include "src/audio/AudioPlayer.h";

using namespace std;

int main() {
    AudioPlayer audio_player;

    const char * filename = "/Users/tomasboda/Desktop/never-gonna-give-u-up.wav";
    audio_player.play_audio(filename);

    return 0;
}
