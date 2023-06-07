#pragma once

#include <gtkmm.h>

// The Gio List Store
class MyItem : public Glib::ObjectBase
{
public:
    static Glib::RefPtr<MyItem> create(Glib::ustring file_name1, std::string path1){
        MyItem *item = new MyItem;
        item->file_name = file_name1;
        item->path = path1;
        item->icon_name = "folder";
        return Glib::RefPtr<MyItem>(item);
    }
    Glib::ustring file_name;
    Glib::ustring icon_name;
    std::string path;
};

// These typedefs is to simplify the complex type names...
typedef Glib::RefPtr<Gtk::SignalListItemFactory> MyFactory;
typedef Glib::RefPtr<Gtk::SingleSelection> MySelection;
typedef Glib::RefPtr<Gio::ListStore<MyItem>> MyStore;
typedef Glib::RefPtr<Gtk::ColumnViewColumn> MyColumn;

class MyPrefs : public Gtk::Window
{
public:
    MyPrefs();

private:
    // Child widgets
    Gtk::ColumnView folders_view, images_view;
    Gtk::Box main_box, views_box, buttons_box;

    // The Selection in a store
    MySelection folder_select;
    // The store to save the item
    MyStore folder_store;
    // Item Factory to renderer the objects
    MyFactory folder_image_factory, folder_string_factory;
    MyColumn folder_image_column, folder_string_column;
    Gtk::Label label_folder;
    Gtk::Image image_folder;

    // Timer to scan the selection, for the absense of "changed" signal
    sigc::connection selection_timer;
    bool timeout_func();

    // Signal Handlers
    void folder_image_setup(const Glib::RefPtr<Gtk::ListItem> &item);
    void folder_image_bind(const Glib::RefPtr<Gtk::ListItem> &item);
    void folder_string_setup(const Glib::RefPtr<Gtk::ListItem> &item);
    void folder_string_bind(const Glib::RefPtr<Gtk::ListItem> &item);
};
