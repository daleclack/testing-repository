#pragma once

#include <gtkmm.h>

class MainWin : public Gtk::ApplicationWindow
{
public:
    MainWin();

private:
    // Child widgets
    Gtk::Picture m_background;
    Gtk::Overlay m_overlay;

    // Context Menu
    Glib::RefPtr<Gtk::Builder> menu_builder;
    Gtk::PopoverMenu context_menu;

    // Gesture for right click
    Glib::RefPtr<Gtk::GestureClick> right_click;

    // Signal Handler
    void pressed(int n_click, double x, double y);
};
