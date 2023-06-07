#pragma once

#include <gtkmm.h>
#include "MyPrefs.hh"

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

    // Prefs Window
    MyPrefs prefs_win;

    // Signal Handler
    void pressed(int n_click, double x, double y);
    void back_activated();
};
