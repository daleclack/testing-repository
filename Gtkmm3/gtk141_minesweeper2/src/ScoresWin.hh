#pragma once

#include <gtkmm.h>
#include "jsonfile.hh"

class ScoresWin : public Gtk::Window{
    public:
        static ScoresWin *create();
        ScoresWin(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade);
    
    private:
        Glib::RefPtr<Gtk::Builder> ref_builder;
};
