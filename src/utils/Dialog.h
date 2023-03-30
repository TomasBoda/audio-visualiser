#include <wx/wx.h>
#include <string>

#ifndef FFT_MUSIC_VISUALISER_MESSAGEDIALOG_H
#define FFT_MUSIC_VISUALISER_MESSAGEDIALOG_H

class Dialog {
public:
    static void show_error_message(const std::string & message) {
        wxMessageDialog dialog(NULL, message,"Error",wxOK | wxCENTRE | wxSTAY_ON_TOP);
        dialog.SetIcon(wxNullIcon);
        int result = dialog.ShowModal();

        if (result == wxID_OK) {
            std::exit(1);
        }
    }

    static std::string show_file_select() {
        wxFileDialog fileDialog(NULL, "Select an audio file", "", "", "All files (*.wav)|*.wav|(*.mp3)|*.mp3", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

        if (fileDialog.ShowModal() == wxID_CANCEL) {
            Dialog::show_error_message("No file selected, exiting...");
        }

        wxString filePath = fileDialog.GetPath();
        std::string file = filePath.ToStdString();

        return file;
    }
};

#endif
