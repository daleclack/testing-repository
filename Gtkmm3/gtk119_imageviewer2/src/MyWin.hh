#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window{
    public:
        MyWin();
    private:
        //Child widgets
        Gtk::ScrolledWindow sw;
        Gtk::Image image;
        Gtk::Box main_box;

        //Gesture control
        
        //Signal Handlers
};
