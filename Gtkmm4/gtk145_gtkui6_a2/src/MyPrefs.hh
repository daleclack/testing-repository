#pragma once

#include <gtkmm.h>

class MyPrefs : public Gtk::Window
{
public:
    MyPrefs();
private:
    // Title Widget
    Gtk::HeaderBar header;
    Gtk::StackSwitcher *stack_switcher;

    // Child Widget
    Gtk::Stack *main_stack;
    Gtk::Box *stack_box;
    Glib::RefPtr<Gtk::Builder> ref_builder;
};