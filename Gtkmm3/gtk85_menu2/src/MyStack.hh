#pragma once

#include <gtkmm.h>

class MyStack{
public:
    MyStack();
    Gtk::Stack *stack;
private:
    //Main builder
    Glib::RefPtr<Gtk::Builder> ref_builder;
    //Child widgets
    Gtk::Overlay *main_overlay,*login_overlay;
    Gtk::Box *user_box;
    Gtk::Image *user_image;
    Gtk::Button *login_btn;
    //Signal Handlers
    void btnlogin_clicked();
};
