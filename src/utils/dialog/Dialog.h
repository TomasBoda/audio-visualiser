#ifndef FFT_MUSIC_VISUALISER_DIALOG_H
#define FFT_MUSIC_VISUALISER_DIALOG_H

#include <wx/wx.h>
#include <string>

class Dialog {
public:
    static void show_error_message(const std::string & message);
    static std::string show_file_select();
};

#endif
