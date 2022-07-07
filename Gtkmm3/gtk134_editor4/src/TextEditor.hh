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
    Gtk::ToggleButton search_button;
    Glib::RefPtr<Gtk::Builder> menu_builder;

    //SearchBar
    Gtk::SearchBar searchbar;
    Gtk::SearchEntry search_entry;
    Gtk::Box searchbox;
    Gtk::Button search_up, search_down;
    Glib::RefPtr<Glib::Binding> search_binding;
    Gtk::TextIter curr_iter_up, curr_iter_down;

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
    bool file_opened;

    //Signal Handlers

    // File Operation functions
    void btnopen_clicked();
    void opendialog_response(int response);
    void btnsave_clicked();
    void btnsaveas_clicked();
    void savedialog_response(int response);

    // Copy, Paste and text operations
    void btncopy_clicked();
    void btnpaste_clicked();
    void btnclose_clicked();
    void buffer1_changed();
    void clipboard_receive(const Glib::ustring &text);
    void infobar_response(int response);

    // Search funtion
    void search_entry_changed();
    void search_forward();
    void search_backward();
};
