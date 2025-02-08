#pragma once

#include <gtkmm.h>

class MsgDialog : public Gtk::Window
{
public:
    MsgDialog();
    void show_message(const Glib::ustring& message);

protected:
    bool on_close_request() override
    {
        set_visible(false);
        return true;
    }

private:
    Gtk::HeaderBar header_bar;
    Gtk::Label label_msg;
    Gtk::Button btn_ok;
};