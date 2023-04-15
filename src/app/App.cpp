#include "App.h"

bool App::OnInit() {
    const char * filename = global::FILENAME;

    audio_player = std::make_unique<AudioPlayer>();
    observer = std::make_unique<Observer>(std::move(audio_player));
    observer->play(filename);
    window = std::make_unique<Window>();
    window->set_observer(std::move(observer));

    return true;
}
