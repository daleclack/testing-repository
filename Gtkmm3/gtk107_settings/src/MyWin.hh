#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window{ 
    public:
        static MyWin * create();
        MyWin(BaseObjectType *cobject,const Glib::RefPtr<Gtk::Builder>& builder);
        ~MyWin();
    private:
        Glib::RefPtr<Gtk::Builder> ref_builder;
        Glib::RefPtr<Gio::Settings> m_settings;
};
