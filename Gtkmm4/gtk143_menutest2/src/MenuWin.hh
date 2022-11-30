#pragma once

#include <gtkmm.h>
#include "Win1.hh"
#include "Win2.hh"

enum class WinShown
{
    DEFAULT,
    WIN_1,
    WIN_2
};

class MenuWin : public Gtk::ApplicationWindow
{
public:
    MenuWin();
    ~MenuWin();

private:
    // Child Widgets
    Gtk::PopoverMenuBar *menu_bar;
    Gtk::Box main_box, btn_box;
    Gtk::Button btn_main, btn_win1, btn_win2;
    Gtk::Label label1;

    // Menu Models
    Glib::RefPtr<Gtk::Builder> builder_def, builder_win1, builder_win2;
    Glib::RefPtr<Gio::MenuModel> model_default, model_win1, model_win2;

    // Windows
    Win1 window1;
    Win2 window2;

    // Signal Handlers
    void btnmain_clicked();
    void btnwin1_clicked();
    void btnwin2_clicked();
    void new_win1();
    void quit_win1();
    void new_win2();
    void quit_win2();
};