#pragma once

#include <gtkmm.h>
#include "MyPanel.hh"

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
    Gtk::Picture login_background;
    Gtk::Image login_image;
    Gtk::Label login_label;
    Gtk::Button login_button;
    Gtk::Overlay *login_page;
    Gtk::Box *main_page, *panel_area;

    //
    MyPanel panel1;

    // Signal handlers
    void login_button_clicked();
};