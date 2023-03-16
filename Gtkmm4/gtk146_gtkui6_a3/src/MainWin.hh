#pragma once

#include <gtkmm.h>
#include "MenuBar.hh"
#include "MyPrefs.hh"

class MainWin : public Gtk::ApplicationWindow
{
public:
    MainWin();

private:
    // Child Widgets
    MenuBar menu_bar;
    Gtk::Box main_box, btn_box;
    Gtk::Button btn_main, btn_win1, btn_win2;
    Gtk::Picture background;
    Gtk::Label label1;
    Gtk::Overlay overlay1;

    // Style provider
    Glib::RefPtr<Gtk::CssProvider> provider;

    // Menu for right click
    Glib::RefPtr<Gtk::GestureClick> gesture_right;
    Glib::RefPtr<Gtk::Builder> context_builder;
    Gtk::PopoverMenu context_menu;
    void press(int n_press, double x, double y);

    // Preferences window
    MyPrefs prefs_win;

    // Signal Handlers for context menu
    void main_about();
    void prefs_activated();
};