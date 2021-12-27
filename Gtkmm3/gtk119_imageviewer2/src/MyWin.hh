#pragma once

#include <gtkmm.h>
#include "MyImage.hh"

class MyWin : public Gtk::Window{
    public:
        MyWin();
    private:
        //Child widgets
        Gtk::ScrolledWindow sw;
        MyImage image_area;
        Gtk::Box main_box,btnbox;
        Gtk::Button btnopen;
        Gtk::Scale scale;
        Glib::RefPtr<Gtk::Adjustment> m_adjustment;
        Glib::RefPtr<Gtk::FileChooserNative> dialog;

        //Gesture control
        
        //Signal Handlers
        void btnopen_clicked();
        void dialog_response(int response_id);
        void scale_changed();
};
