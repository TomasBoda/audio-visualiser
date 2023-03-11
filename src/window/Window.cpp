#include <vector>
#include <wx/wx.h>
#include "Window.h"

using namespace std;

void Window::OnPaint(wxPaintEvent & event) {
    wxPaintDC dc(this);
}

wxBEGIN_EVENT_TABLE(Window, wxFrame)
wxEND_EVENT_TABLE()

