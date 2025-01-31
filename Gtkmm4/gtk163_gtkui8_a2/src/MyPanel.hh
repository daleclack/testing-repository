#pragma once

#include <gtkmm.h>

class MyPanel
{
public:
    Gtk::Box *panel_box;
    MyPanel();

private:
    Glib::RefPtr<Gtk::Builder> builder;
};
