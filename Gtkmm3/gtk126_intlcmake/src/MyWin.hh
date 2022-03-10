#pragma once

#include <gtkmm.h>
#include <glibmm/i18n.h>
#include "MyPrefs.hh"

class MyWin : public Gtk::Window
{
public:
    MyWin();

private:
    //Child Widgets
    Gtk::Overlay m_overlay;
    Gtk::Image m_back;
    Gtk::Button btnback;

    //Background Preferences
    MyPrefs prefs_win;

    //Signal Handlers
    void btnback_clicked();
};
