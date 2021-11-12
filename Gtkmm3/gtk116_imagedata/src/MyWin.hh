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
        Gtk::Box hbox,btnbox;
        Gtk::Label label_pos,label_rgba;
        Gtk::ColorButton color_btn;
        Gtk::DrawingArea draw_area;
        Glib::RefPtr<Gdk::Pixbuf> pixbuf;
        Glib::RefPtr<Gdk::Pixbuf> sized;

        //Get Mouse Position
        Glib::RefPtr<Gtk::GestureMultiPress> gesture;
        
        //Signal Handlers
        Glib::RefPtr<Gtk::FileChooserNative> dialog;
        void get_pixel_color(int x,int y);
        void btnback_clicked();
        void set_background(int reponse_id);
        void gesture_pressed(int n_press,double x,double y);
};