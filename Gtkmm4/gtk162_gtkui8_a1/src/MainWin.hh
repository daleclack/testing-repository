#pragma once

#include <gtkmm.h>
#include "Window1.hh"
#include "Window2.hh"

class MainWin : public Gtk::ApplicationWindow
{
public:
    MainWin();
    virtual ~MainWin();

protected:
    // Signal handlers:
    //  void on_button_clicked();
private:
    // Window and dock controls
    Gtk::Overlay overlay;
    Gtk::Box menu_box, dock_box;
    Gtk::PopoverMenuBar global_menu;
    Gtk::Button win1_button, win2_button;

    // Main menu objects
    Glib::RefPtr<Gtk::Builder> main_builder;

    // Two windows to control
    Window1 win1;
    Window2 win2;

    // Signal Handlers
    void btnwin1_clicked();
    void btnwin2_clicked();
};
