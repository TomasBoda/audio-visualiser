#include "App.h"

bool App::OnInit() {
    const char * filename = global::FILENAME;

    audio_player = std::make_unique<AudioPlayer>();
    observer = std::make_unique<Observer>(audio_player);
    observer->play(filename);
    window = std::make_unique<Window>();
    window->set_observer(observer);

    return true;
}
