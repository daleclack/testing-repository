#pragma once

#include <gtkmm.h>

class MyStack
{
public:
    Gtk::Stack *m_stack;
    MyStack();

private:
    // Object builder
    Glib::RefPtr<Gtk::Builder> m_builder;

    // Child widgets
    Gtk::Box login_box;
    Gtk::Image login_image;
    Gtk::Label login_label;
    Gtk::Button login_button;
    Gtk::Overlay *login_page;
    Gtk::Box *main_page;
};