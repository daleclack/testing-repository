#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window{
public:
    MyWin();
    virtual ~MyWin();
private:
    //Child widgets
    Glib::RefPtr<Gtk::Builder> menu_builder;
    Gtk::Overlay overlay;
    Gtk::DrawingArea draw_area;
    Gtk::PopoverMenu popover;
    //Gesture Widgets
    Glib::RefPtr<Gtk::GestureMultiPress> gesture;
    void btn_pressed(int n_press,double x,double y);
};