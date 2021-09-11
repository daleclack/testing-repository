#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window{ 
    public:
        static MyWin * create();
        MyWin(BaseObjectType *cobject,const Glib::RefPtr<Gtk::Builder>& builder);
    private:
        //Child Widgets
        Glib::RefPtr<Gtk::Builder> ref_builder;
        Glib::RefPtr<Gio::Settings> m_settings;
        Gtk::Button* btnprefs;

        //Signal Handlers
        void btnprefs_clicked();
        void on_hide_window(Gtk::Window* window);
};
