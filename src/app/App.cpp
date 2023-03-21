#include "App.h"
#include "../gui/Window.h"
#include "../audio/AudioPlayer.h"
#include "../utils/Dialog.h"

bool App::OnInit() {
    std::string file = Dialog::showFileSelect();

    audio_player = new AudioPlayer();
    audio_player->play_audio(file);
    window = new Window();

    return true;
}
