#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window{
    public:
        MyWin();
    private:
        //Child Widgets
        Gtk::Image background;
        Glib::RefPtr<Gdk::Pixbuf> pixbuf;
        Glib::RefPtr<Gdk::Pixbuf> sized;
        //Signal Handlers
        void get_pixel_color(int x,int y);
};