#pragma once

#include <gtkmm.h>

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
};
