#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window{
    public:
        MyWin();
    private:
        //Child Widgets
        Gtk::Overlay m_overlay;
        Gtk::Button btn_back;
        Gtk::Image background;
        Glib::RefPtr<Gdk::Pixbuf> pixbuf;
        Glib::RefPtr<Gdk::Pixbuf> sized;
        //Get Mouse Position
        Glib::RefPtr<Gtk::Gesture> gesture;
        //Signal Handlers
        Glib::RefPtr<Gtk::FileChooserNative> dialog;
        void get_pixel_color(int x,int y);
        void btnback_clicked();
        void set_background(int reponse_id);
};