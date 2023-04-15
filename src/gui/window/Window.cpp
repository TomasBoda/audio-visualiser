#include "Window.h"

Window::Window() {
    equalizer_visualiser = new Equalizer();
    circular_visualiser = new Circular();
    volumes_visualiser = new Volumes();

    visualiser = equalizer_visualiser;

    init_menu_bar();
}

void Window::render(Graphics graphics) {
    visualiser->render_visualiser(graphics);
}

void Window::update() {
    visualiser->update_visualiser();
}

void Window::on_choose(Event event) {
    // select new local audio file to be played
    std::string filename = Dialog::show_file_select();
    observer->play(filename);
}

void Window::on_quit(Event event) {
    std::exit(0);
}

void Window::on_resume(Event event) {
    observer->resume();
}

void Window::on_pause(Event event) {
    observer->pause();
}

void Window::on_equalizer_select(Event event) {
    visualiser = equalizer_visualiser;
}

void Window::on_circular_select(Event event) {
    visualiser = circular_visualiser;
}

void Window::on_volumes_select(Event event) {
    visualiser = volumes_visualiser;
}

void Window::init_menu_bar() {
    menu_bar = new wxMenuBar();

    wxMenu * file_menu = new wxMenu();
    file_menu->Append(wxID_ANY, "&Choose new file...\tCtrl+N");
    file_menu->Append(wxID_ANY, "&Quit\tCtrl+Q");
    Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::on_choose, this, file_menu->GetMenuItems()[0]->GetId());
    Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::on_quit, this, file_menu->GetMenuItems()[1]->GetId());
    menu_bar->Append(file_menu, "&File");

    wxMenu * playback_menu = new wxMenu();
    playback_menu->Append(wxID_ANY, "&Resume\tCtrl+R");
    playback_menu->Append(wxID_ANY, "&Pause\tCtrl+P");
    Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::on_resume, this, playback_menu->GetMenuItems()[0]->GetId());
    Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::on_pause, this, playback_menu->GetMenuItems()[1]->GetId());
    menu_bar->Append(playback_menu, "&Playback");

    wxMenu * visualiser_menu = new wxMenu();
    visualiser_menu->Append(wxID_ANY, "Equalizer\tCtrl+E");
    visualiser_menu->Append(wxID_ANY, "Circular\tCtrl+C");
    visualiser_menu->Append(wxID_ANY, "Volumes\tCtrl+V");
    Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::on_equalizer_select, this, visualiser_menu->GetMenuItems()[0]->GetId());
    Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::on_circular_select, this, visualiser_menu->GetMenuItems()[1]->GetId());
    Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::on_volumes_select, this, visualiser_menu->GetMenuItems()[2]->GetId());
    menu_bar->Append(visualiser_menu, "&Visualiser");

    SetMenuBar(menu_bar);
}

