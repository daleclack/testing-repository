#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window{
public:
    MyWin();
private:
    //Child Widgets
    Gtk::FontButton fontbtn;
    Gtk::Label label1;
    Gtk::Box main_box;
    //Signal Handlers
    void font_changed();
};
