#include "App.h"
#include "../gui/window/Window.h"
#include "../audio/AudioPlayer.h"
#include "../utils/Dialog.h"

bool App::OnInit() {
    //std::string file = Dialog::show_file_select();
    const char * file = global::FILENAME;

    audio_player = new AudioPlayer();
    observer = new Observer(audio_player);
    //audio_player->play_audio(file);
    window = new Window();
    window->set_observer(observer);
    observer->play_audio(file);

    return true;
}
