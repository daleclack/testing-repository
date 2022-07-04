#pragma once

#include <gtkmm.h>

class TextEditor : public Gtk::ApplicationWindow{
public:
    TextEditor();
private:
    //Header widgets
    Gtk::HeaderBar header;
    Gtk::MenuButton menubtn;
    Gtk::Popover popover;
    Glib::RefPtr<Gtk::Builder> menu_builder;

    //Window widgets
    Gtk::Box vbox,hbox,*infobox;
    Gtk::ScrolledWindow sw1,sw2;
    Glib::RefPtr<Gtk::TextBuffer> buffer1;
    Gtk::TextView textview1;
    Gtk::InfoBar infobar;
    Gtk::Label label1;
    //File Dialog
    Glib::RefPtr<Gtk::FileChooserNative> dialog;
    //Signal Handlers
    void btnopen_clicked();
    void opendialog_response(int response);
    void btnsave_clicked();
    void savedialog_response(int response);
    void btncopy_clicked();
    void btnpaste_clicked();
    void btnclear_clicked();
    void buffer1_changed();
    void clipboard_receive(const Glib::ustring &text);
    void infobar_response(int response);
};
