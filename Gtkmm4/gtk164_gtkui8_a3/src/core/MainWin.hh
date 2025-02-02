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
    // Child widgets
    Gtk::Overlay *main_overlay;
    Gtk::Picture *main_background;

    // Builder for the window
    Glib::RefPtr<Gtk::Builder> ref_builder;

    // Other widgets
    MyStack main_stack;
};
