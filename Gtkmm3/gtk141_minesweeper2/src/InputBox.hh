#pragma once

#include <gtkmm.h>

class InputBox : public Gtk::Dialog{
    public:
        static InputBox *create();
        InputBox(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade);
    
    private:
        Glib::RefPtr<Gtk::Builder> ref_builder;
};