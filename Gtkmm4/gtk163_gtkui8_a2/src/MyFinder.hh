#pragma once

#include <gtkmm.h>

class MyFinder
{
public:
    Gtk::Stack *menu_stack;
    MyFinder();

private:
    Glib::RefPtr<Gtk::Builder> builder;

    // Child widgets
    Gtk::StackSwitcher *inner_switcher;
    Gtk::Stack *inner_stack;
};