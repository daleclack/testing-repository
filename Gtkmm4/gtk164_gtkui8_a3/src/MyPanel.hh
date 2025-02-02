#pragma once

#include <gtkmm.h>
#include "AppMenu.hh"

class MyPanel
{
public:
    Gtk::Box *panel_box;
    MyPanel();

private:
    Glib::RefPtr<Gtk::Builder> builder;

    // Child widgets
    Gtk::Button *btnstart;
    Gtk::Stack *apps_stack;
    Gtk::Box *apps_box;

    // The App Menu
    AppMenu app_menu;

    // Signal handlers
    void btnstart_clicked();
};
