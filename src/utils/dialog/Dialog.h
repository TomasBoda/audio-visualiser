#ifndef FFT_MUSIC_VISUALISER_DIALOG_H
#define FFT_MUSIC_VISUALISER_DIALOG_H

#include <wx/wx.h>
#include <string>

class Dialog {
public:
    /*
     * Show an error dialog
     * This method triggers an error dialog with a custom message
     * @param message message to be displayed
     */
    static void show_error_message(const std::string & message);
    /*
     * Show a file select dialog
     * This method triggers a file selection dialog
     * @return path of the selected audio wave file
     */
    static std::string show_file_select();
};

#endif
