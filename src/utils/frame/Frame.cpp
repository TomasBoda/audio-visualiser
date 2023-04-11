#include "Frame.h"

Frame::Frame(): wxFrame(NULL, wxID_ANY, "Music Visualiser", wxDefaultPosition, wxDefaultSize) {
    initialize();
    initialize_timers();
    initialize_window();
}

Frame::~Frame() {
    render_timer->Stop();
    update_timer->Stop();
    delete render_timer;
    delete update_timer;
}

void Frame::OnPaint(wxPaintEvent &event) {
    // double buffered rendering - implemented due to issues on Windows computers
    wxPaintDC graphics(this);
    wxBitmap bitmap(GetClientSize().GetWidth(), GetClientSize().GetHeight());
    wxMemoryDC memory_graphics(bitmap);
    memory_graphics.SetBackground(wxColour(0, 0, 0));
    memory_graphics.Clear();

    render(memory_graphics);

    graphics.Blit(0, 0, GetClientSize().GetWidth(), GetClientSize().GetHeight(), &memory_graphics, 0, 0);
}

void Frame::OnSize(wxSizeEvent &event) {
    wxSize size = event.GetSize();
    global::WIDTH = size.GetWidth();
    global::HEIGHT = size.GetHeight();
}

void Frame::OnClose(wxCloseEvent &event) {
    render_timer->Stop();
    update_timer->Stop();
    Destroy();
}

void Frame::on_render_timer(wxTimerEvent &event) {
    Refresh();
}

void Frame::on_update_timer(wxTimerEvent &event) {
    update();
}

void Frame::initialize_window() {
    Bind(wxEVT_PAINT, &Frame::OnPaint, this);
    Bind(wxEVT_SIZE, &Frame::OnSize, this);

    init_default_size();

    Center();
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetDoubleBuffered(true);
    Show(true);
}

void Frame::init_default_size() {
    wxDisplay display;
    wxRect screenRect = display.GetClientArea();
    SetSize(screenRect);

    global::WIDTH = screenRect.width;
    global::HEIGHT = screenRect.height;
}

void Frame::initialize_timers() {
    render_timer = new wxTimer(this, wxID_ANY);
    update_timer = new wxTimer(this, wxID_ANY);

    Bind(wxEVT_TIMER, &Frame::on_render_timer, this, render_timer->GetId());
    Bind(wxEVT_TIMER, &Frame::on_update_timer, this, update_timer->GetId());

    render_timer->Start(render_timer_refresh_rate);
    update_timer->Start(update_timer_refresh_rate);
}
