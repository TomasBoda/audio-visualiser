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

void Window::on_quit(wxCommandEvent &event) {
    std::exit(0);
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
    file_menu->Append(wxID_ANY, "&Quit\tCtrl+Q");
    Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::on_quit, this, file_menu->GetMenuItems()[0]->GetId());
    menu_bar->Append(file_menu, "&File");

    wxMenu * visualiser_menu = new wxMenu();
    visualiser_menu->Append(wxID_ANY, "Equalizer\tCtrl+E");
    visualiser_menu->Append(wxID_ANY, "Circular\tCtrl+C");
    Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::on_equalizer_select, this, visualiser_menu->GetMenuItems()[0]->GetId());
    Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::on_circular_select, this, visualiser_menu->GetMenuItems()[1]->GetId());
    menu_bar->Append(visualiser_menu, "&Visualiser");

    SetMenuBar(menu_bar);
}

