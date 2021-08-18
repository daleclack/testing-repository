#pragma once

#include <gtkmm.h>
#include "SetDialog.hh"

class MyWin : public Gtk::Window{
public:
    MyWin();
private:
    //Child Widgets
    Gtk::Overlay m_overlay;
    Gtk::Image m_back;
    Gtk::Button btnset;
    
    //Setting Dialog and config
    conf_map configs;
    SetDialog dialog1;

    //Signal Handlers
    void btnset_clicked();
    void default_background();
};
