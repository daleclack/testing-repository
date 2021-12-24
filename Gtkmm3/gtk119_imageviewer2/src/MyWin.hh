#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window{
    public:
        MyWin();
    private:
        //Child widgets
        Gtk::ScrolledWindow sw;
        Gtk::DrawingArea image_area;
        Gtk::Box main_box,btnbox;

        //Gesture control
        
        //Signal Handlers
};
