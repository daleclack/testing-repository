#pragma once

#include <gtkmm.h>
#include "Win1.hh"
#include "Win2.hh"
#include "MenuBar.hh"

class MenuWin : public Gtk::ApplicationWindow
{
public:
    MenuWin();

private:
    // Child Widgets
    MenuBar menu_bar;
    Gtk::Box main_box, btn_box;
    Gtk::Button btn_main, btn_win1, btn_win2;
    Gtk::Label label1;
    Gtk::Overlay overlay1;

    // Windows
    Win1 window1;
    Win2 window2;

    // Signal Handlers
    void btnmain_clicked();
    void btnwin1_clicked();
    void btnwin2_clicked();
    void new_win1();
    void quit_win1();
    bool win1_closed();
    void new_win2();
    void quit_win2();
    bool win2_closed();
    void show_about_win1();
    void show_about_win2();
};