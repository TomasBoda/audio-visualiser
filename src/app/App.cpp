#include "App.h"
#include "../utils/dialog/Dialog.h"

bool App::OnInit() {
    //std::string filename = Dialog::show_file_select();
    const char * filename = global::FILENAME;

    audio_player = new AudioPlayer();

    observer = new Observer(audio_player);
    observer->play(filename);

    window = new Window();
    window->set_observer(observer);

    return true;
}
