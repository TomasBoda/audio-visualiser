#include "App.h"

bool App::OnInit() {
    const char * filename = global::FILENAME;

    audio_player = new AudioPlayer();

    observer = new Observer(audio_player);
    observer->play(filename);

    window = new Window();
    window->set_observer(observer);

    return true;
}
