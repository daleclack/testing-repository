#pragma once

#include <gtkmm.h>

class GtkWin : public Gtk::Window{
    public:

    GtkWin();
    virtual ~GtkWin();

    protected:

    bool activity_mode=false;

    //Child widgets
    Gtk::ProgressBar progress1;
    Gtk::Box hbox;
    Gtk::CheckButton checkshow,check_activity,check_inverted;
    Gtk::Button btn_exit;
    sigc::connection connection_timeout;

    //Signal Handlers
    bool on_timeout();
    void checkshow_clicked();
    void activity_clicked();
    void invert_clicked();
    void exit_clicked();
};