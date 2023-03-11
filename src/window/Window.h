#include <iostream>
#include <vector>
#include <wx/wx.h>

#ifndef FFT_MUSIC_VISUALISER_WINDOW_H
#define FFT_MUSIC_VISUALISER_WINDOW_H

class Window : public wxFrame {
public:
    Window(const wxString & title, const wxPoint & pos, const wxSize & size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
        Connect(wxEVT_PAINT, wxPaintEventHandler(Window::OnPaint));

        SetSize(size);
        SetPosition(pos);
        Show(true);
    };

    void OnPaint(wxPaintEvent & event);
private:
    wxDECLARE_EVENT_TABLE();
};

#endif
