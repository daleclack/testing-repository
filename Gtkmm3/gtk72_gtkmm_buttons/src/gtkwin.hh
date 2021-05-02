#pragma once

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/separator.h>
#include <gtkmm/box.h>

class GtkWin : public Gtk::Window{
public:
    GtkWin();
    virtual ~GtkWin();
protected:
    Gtk::Box hbox;
    Gtk::Button button1;
    Gtk::CheckButton check1;
    Gtk::Separator separtor,separtor1;
    Gtk::RadioButton rb[3];
    void get_config();
    void write_config();
};
