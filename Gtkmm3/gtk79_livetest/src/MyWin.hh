#pragma once

#include <gtkmm.h>
#include "BackGround.hh"

class MyWin : public Gtk::Window{
public:
    MyWin();
    virtual ~MyWin();
protected:
    //Signal handlers
    void btnback_clicked();
    //Child widgets
    Gtk::Overlay overlay;
    Gtk::Image back;
    Gtk::Button btn_back;
    BackGround back_dialog;
};
