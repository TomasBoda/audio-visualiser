#include "Window.h"

Window::Window() {
    equalizer_visualiser = new Equalizer();
    circular_visualiser = new Circular();
    visualiser = equalizer_visualiser;

    init_menu_bar();
}

void Window::render(wxDC &graphics) {
    visualiser->render_visualiser(graphics);
}

void Window::update() {
    visualiser->update_visualiser();
}

void Window::on_choose(wxCommandEvent &event) {
    std::string filename = Dialog::show_file_select();
    observer->play(filename);
}

void Window::on_quit(wxCommandEvent &event) {
    std::exit(0);
}

void Window::on_resume(wxCommandEvent &event) {
    observer->resume();
}

void Window::on_pause(wxCommandEvent &event) {
    observer->pause();
}

void Window::on_equalizer_select(wxCommandEvent &event) {
    visualiser = equalizer_visualiser;
}

void Window::on_circular_select(wxCommandEvent &event) {
    visualiser = circular_visualiser;
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
    Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::on_equalizer_select, this, visualiser_menu->GetMenuItems()[0]->GetId());
    Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::on_circular_select, this, visualiser_menu->GetMenuItems()[1]->GetId());
    menu_bar->Append(visualiser_menu, "&Visualiser");

    SetMenuBar(menu_bar);
}

