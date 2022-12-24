#pragma once

#include <gtkmm.h>

enum class WinShown
{
    DEFAULT,
    WIN_1,
    WIN_2
};

class MenuBar
{
public:
    MenuBar();
    ~MenuBar();
    void change_menu(WinShown win_id);
    Gtk::PopoverMenuBar *menubar;

private:
    // Menu Models
    Glib::RefPtr<Gtk::Builder> builder_def, builder_win1, builder_win2;
    Glib::RefPtr<Gio::MenuModel> model_default, model_win1, model_win2;
};
