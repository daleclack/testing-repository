#pragma once

#include <gtkmm.h>
#include "NewDialog.hh"
#include "MsgDialog.hh"

class FileBtn : public Gtk::Button
{
public:
    FileBtn(const Glib::ustring &label)
    {
        set_label(label);
    }

    Glib::ustring file_path;
    guint id;
};

class FileWindow : public Gtk::Window
{
public:
    FileWindow();

private:
    // Input Box
    Gtk::Window input_window;
    Gtk::Box input_box;
    Gtk::Entry input_entry;
    Gtk::Button btn_ok, btn_cancel;

    Gtk::Window dialog;
    Gtk::Box dialog_box;
    Gtk::Button dialog_ok;

    // Child widgets
    Gtk::Box main_box, place_box, views_box;
    Gtk::Entry place_entry;
    Gtk::ListView places_view;
    Gtk::ScrolledWindow main_scroller, places_scroller;
    Gtk::ColumnView main_view;
    Gtk::Button btn_add, btn_up, btn_del;

    // List for sidebar
    Glib::RefPtr<Gtk::StringList> places_list;
    Glib::RefPtr<Gtk::SingleSelection> places_selection;
    Glib::RefPtr<Gtk::SignalListItemFactory> places_factory;
    void places_setup(const Glib::RefPtr<Gtk::ListItem> &item);
    void places_bind(const Glib::RefPtr<Gtk::ListItem> &item);

    // Directory list
    Glib::RefPtr<Gtk::DirectoryList> dir_list;
    Glib::RefPtr<Gtk::SingleSelection> dir_selection;
    void folder_item_activated(guint pos);

    // Factory for icons
    Glib::RefPtr<Gtk::SignalListItemFactory> icon_factory;
    void icon_setup(const Glib::RefPtr<Gtk::ListItem> &item);
    void icon_bind(const Glib::RefPtr<Gtk::ListItem> &item);

    // Factory for filenames
    Glib::RefPtr<Gtk::SignalListItemFactory> name_factory;
    void name_setup(const Glib::RefPtr<Gtk::ListItem> &item);
    void name_bind(const Glib::RefPtr<Gtk::ListItem> &item);

    // Factory for types
    Glib::RefPtr<Gtk::SignalListItemFactory> type_factory;
    void type_setup(const Glib::RefPtr<Gtk::ListItem> &item);
    void type_bind(const Glib::RefPtr<Gtk::ListItem> &item);

    // Factory for sizes
    Glib::RefPtr<Gtk::SignalListItemFactory> size_factory;
    void size_setup(const Glib::RefPtr<Gtk::ListItem> &item);
    void size_bind(const Glib::RefPtr<Gtk::ListItem> &item);

    // Dialog for new folder
    NewDialog new_dialog;

    // Dialog for message
    MsgDialog msg_dialog;

    // Signal handlers
    void btnadd_clicked();
    void btnup_clicked();
    void btnhome_clicked();
    void btndel_clicked();
};