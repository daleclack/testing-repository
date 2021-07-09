#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window{
public:
    MyWin();
private:
    //Child widgets
    Gtk::Box vbox,hbox,btnbox,*infobox;
    Gtk::ScrolledWindow sw1,sw2;
    Glib::RefPtr<Gtk::TextBuffer> buffer1,buffer2;
    Gtk::TextView textview1,textview2;
    Gtk::Button btn_copy,btn_paste;
    Gtk::InfoBar infobar;
    Gtk::Label label1;
    //Signal Handlers
    void btncopy_clicked();
    void btnpaste_clicked();
    void buffer1_changed();
    void clipboard_receive(const Glib::ustring &text);
    void infobar_response(int response);
};
