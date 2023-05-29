#pragma once

#include <gtkmm.h>

class MyPrefs : public Gtk::Window
{
public:
    MyPrefs();
private:
    Glib::RefPtr<Gtk::Builder> stack_builder;
};
