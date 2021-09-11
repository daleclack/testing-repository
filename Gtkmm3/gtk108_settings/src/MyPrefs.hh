#pragma once

#include <gtkmm.h>

class MyPrefs : public Gtk::Dialog{
    public:
        MyPrefs(BaseObjectType *cobject,const Glib::RefPtr<Gtk::Builder> &builder);
        static MyPrefs * create(Gtk::Window &parent);
    private:
        Glib::RefPtr<Gtk::Builder> m_builder;
        Glib::RefPtr<Gio::Settings> m_settings;
        Gtk::SpinButton * m_width,* m_height;
};
