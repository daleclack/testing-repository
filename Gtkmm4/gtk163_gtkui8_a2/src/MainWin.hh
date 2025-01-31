#pragma once

#include <gtkmm.h>
#include "MyStack.hh"

class MainWin : public Gtk::ApplicationWindow
{
public:
    MainWin(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder>& ref_builder1);
    static MainWin *create();
    virtual ~MainWin() {}

protected:
    
private:
    Gtk::Overlay *main_overlay;
    Gtk::Picture *main_background;
    Glib::RefPtr<Gtk::Builder> ref_builder;
};
