#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window{
public:
    MyWin();
private:
    //Child Widgets
    Gtk::FontButton fontbtn;
    Gtk::Button btnsave,btnload;
    Gtk::Label label1;
    Gtk::Box main_box;
    //A Dialog
    Glib::RefPtr<Gtk::FileChooserNative> dialog;
    //Signal Handlers
    void font_changed();
    void save_dialog();
    void load_dialog();
    void load_font(int response);
    void save_font(int response);
};
