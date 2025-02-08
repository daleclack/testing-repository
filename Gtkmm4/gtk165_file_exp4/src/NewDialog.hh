#pragma once

#include <gtkmm.h>

class NewDialog : public Gtk::Window
{
public:
    NewDialog();
    void show_dialog(std::string& path);

protected:
    // Close = hide window
    bool on_close_request() override
    {
        set_visible(false);
        return true;
    }

private:
    // Child widgets
    Gtk::HeaderBar header;
    Gtk::Entry entry_name;
    Gtk::Button btn_ok, btn_cancel;

    // Path information
    std::string info_path;

    // Signal Handlers
    void btnok_clicked();
};