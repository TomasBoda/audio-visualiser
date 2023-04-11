#ifndef FFT_MUSIC_VISUALISER_FRAME_H
#define FFT_MUSIC_VISUALISER_FRAME_H

#include <wx/wx.h>
#include <wx/display.h>
#include <wx/dcbuffer.h>
#include "../../config/config.h"

/*
 * Native window
 * This class represents a native cross-platform window
 */
class Frame : public wxFrame {
public:
    Frame();
    ~Frame();

    /*
     * Initialize the window
     * This method is used to initialize a custom window
     */
    virtual void initialize() {};
    /*
     * Render components in the window
     * This method renders custom components in the window
     * @param graphics graphics object @see wxDC
     */
    virtual void render(Graphics graphics) {};
    /*
     * Update components in the window
     * This method is used for updating custom components in the window
     */
    virtual void update() {};
private:
    wxTimer * render_timer;
    wxTimer * update_timer;

    const size_t render_timer_refresh_rate = 10;
    const size_t update_timer_refresh_rate = 10;

    void OnPaint(wxPaintEvent & event);
    void OnSize(wxSizeEvent & event);
    void OnClose(wxCloseEvent & event);

    void on_render_timer(wxTimerEvent & event);
    void on_update_timer(wxTimerEvent & event);

    /*
     * Initialize window
     * This method initializes a default window
     */
    void initialize_window();
    /*
     * Initialize default window size to fill the current display
     * This method initializes the window dimensions to fil the current display size
     */
    void init_default_size();
    /*
     * Initialize render and update timers
     * This method initializes timers used for rendering and updating components in the window
     */
    void initialize_timers();
};

#endif
