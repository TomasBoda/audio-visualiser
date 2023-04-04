#include "App.h"
#include "../gui/Window.h"
#include "../audio/AudioPlayer.h"
#include "../utils/Dialog.h"

bool App::OnInit() {
    std::string file = Dialog::show_file_select();
    //const char * file = global::FILENAME;

    audio_player = new AudioPlayer();
    audio_player->play_audio(file);
    window = new Window();

    return true;
}
