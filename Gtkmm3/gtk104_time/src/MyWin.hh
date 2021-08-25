#pragma once

#include <gtkmm.h>
#include "../cfgfile2/cfgfile.hh"

class MyWin : public Gtk::Window{
public:
    MyWin();
private:
    //TimeOut Control
    sigc::connection myconnection;
    //Signal Handler
    bool on_timeout();
};
