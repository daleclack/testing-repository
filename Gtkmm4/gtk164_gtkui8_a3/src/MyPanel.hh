#pragma once

#include <gtkmm.h>

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

    // Signal handlers
    void btnstart_clicked();
};
