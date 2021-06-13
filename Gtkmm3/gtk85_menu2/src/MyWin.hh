#pragma once

#include <gtkmm.h>
#include "MyStack.hh"

class MyWin : public Gtk::ApplicationWindow{
public:
    MyWin();
    virtual ~MyWin();
private:
    //Child widgets
    Glib::RefPtr<Gtk::Builder> menu_builder;
    Gtk::Overlay overlay;
    Gtk::DrawingArea draw_area;
    Gtk::Box main_box;
    Gtk::PopoverMenu popover;
    Gtk::Image background;

    //Main Pages
    MyStack main_stack;
    
    //Gesture Widgets
    Glib::RefPtr<Gtk::GestureMultiPress> gesture;
    void btn_pressed(int n_press,double x,double y);

    //Signal Handlers
    void default_background();
    void back_dialog();
    void change_background(int response,Gtk::FileChooserDialog *dialog);
    void about_dialog();
    void win_quit();
};