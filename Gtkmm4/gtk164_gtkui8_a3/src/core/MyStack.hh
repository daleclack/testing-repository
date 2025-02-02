#pragma once

#include <gtkmm.h>
#include "MyPanel.hh"
#include "MyFinder.hh"

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
    Gtk::Box *main_page, *panel_area,
        *topmenu_area, *menu_area;

    // The Left Panel
    MyPanel panel1;

    // The Main Menu
    MyFinder finder1;

    // Signal handlers
    void login_button_clicked();
};