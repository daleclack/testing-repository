#pragma once

#include <gtkmm.h>

class TextEditor : public Gtk::ApplicationWindow{
public:
    TextEditor(BaseObjectType *cobject,const Glib::RefPtr<Gtk::Builder> &ref_builder);
    static TextEditor * create();
private:
    //Header widgets
    // Gtk::HeaderBar header;
    // Gtk::MenuButton menubtn;
    Gtk::Popover *popover;
    Gtk::ToggleButton *search_button;
    Gtk::SearchBar *searchbar;
    Gtk::SearchEntry *search_entry;
    Glib::RefPtr<Gtk::Builder> menu_builder, main_builder;
    Glib::RefPtr<Glib::Binding> m_binding;
    // Gtk::Box *searchbox;

    //Window widgets
    Gtk::Box vbox,hbox,*infobox;
    Gtk::ScrolledWindow sw1,sw2;
    Glib::RefPtr<Gtk::TextBuffer> buffer1;
    Gtk::TextView textview1;
    Gtk::InfoBar infobar;
    Gtk::Label label1;

    //File Dialog
    Glib::RefPtr<Gtk::FileChooserNative> dialog;
    Glib::ustring curr_filename;

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
