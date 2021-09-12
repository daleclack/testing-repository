#pragma once

#include <gtkmm.h>

class MyPrefs : public Gtk::Dialog{
    public:
        MyPrefs(BaseObjectType *cobject,const Glib::RefPtr<Gtk::Builder> &builder);
        static MyPrefs * create(Gtk::Window &parent);
    private:
    //Child Widgets
        Glib::RefPtr<Gtk::Builder> m_builder;
        Glib::RefPtr<Gio::Settings> m_settings;
        Glib::RefPtr<Gtk::FileChooserNative> dialog;
        Gtk::SpinButton * m_width,* m_height;
        Gtk::Entry * back_entry;
        Gtk::Button * btnopen,* btnget,* btndefback,* btndefsize;
    
    //Signal Handlers
        void btnopen_clicked();
        void btnget_clicked();
        void btndefback_clicked();
        void btndefsize_clicked();
        void dialog_response(int response_id);
};
