#pragma once

#include <gtkmm.h>

class GtkWin : public Gtk::Window
{
    public:

    GtkWin();
    virtual ~GtkWin();

    protected:

    //Child widgets
    Gtk::Box hbox;
    Gtk::Box vbox;
    Gtk::TextView m_textview;
    Gtk::ScrolledWindow sw;
    Gtk::Button btn_clear,btn_close;
    Glib::RefPtr<Gtk::TextBuffer> m_textbuffer;
    Gtk::InfoBar m_infobar;
    Gtk::Label info_label;

    //Signal Handlers
    void clear_clicked();
    void close_clicked();
    void infobar_reponse(int response);
    void buffer_changed();
};