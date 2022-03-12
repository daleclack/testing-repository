#pragma once

#include <gtkmm.h>
#include <glibmm/i18n.h>
#include "ColorPicker.hh"

class MyWin : public Gtk::Window
{
public:
    MyWin(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade);
    static MyWin *create();

private:
    Glib::RefPtr<Gtk::Builder> ref_builder;

    // Child Widgets
    Gtk::Box *picker_box, *panel_box, *ref_box;

    // Color Picker
    ColorPicker color_picker;
};