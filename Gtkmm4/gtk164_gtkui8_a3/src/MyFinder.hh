#pragma once

#include <gtkmm.h>

class MyFinder
{
public:
    // The right menu
    Gtk::Stack *menu_stack;

    // The Top menu
    Gtk::Box menu_box;
    MyFinder();

private:
    Glib::RefPtr<Gtk::Builder> builder;

    // Widget for top panel
    Gtk::Label title_label, space_label;
    Gtk::Button btn_computer, btn_audio, btn_wifi,
        btn_battery, btn_search, btn_time, btn_menu;

    // Child widgets for left menu
    Gtk::StackSwitcher *inner_switcher;
    Gtk::Stack *inner_stack;

    sigc::connection timer;

    // Signal handlers
    bool timeout_func();
    void btnmenu_clicked();
};