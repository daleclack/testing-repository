#pragma once

#include <gtkmm.h>

class MyPrefs : public Gtk::Window
{
public:
    MyPrefs();
    void set_background(Gtk::Image *back);

protected:
    class ModelColumns : public Gtk::TreeModelColumnRecord
    {
    public:
        ModelColumns()
        {
            add(m_col_pixbuf);
            add(m_col_path);
            add(m_col_name);
        }
        Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> m_col_pixbuf;
        Gtk::TreeModelColumn<std::string> m_col_path;
        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    };

    ModelColumns n_columns;
    Glib::RefPtr<Gtk::ListStore> folders_store, images_store;

private:
    // Widget for parent window
    Gtk::Image *background1;

    // Child Widgets
    Gtk::TreeView folders_view, images_view;
    Gtk::ScrolledWindow sw_folders, sw_images;
    Gtk::Box main_box, views_box, btnbox;
    Gtk::Button btnadd, btnremove;

    //Folder Open Dialog
    Glib::RefPtr<Gdk::Pixbuf> folder_pixbuf;
    Glib::RefPtr<Gtk::FileChooserNative> dialog;
    void dialog_response(int response_id);

    //Signal Handlers
    void btnadd_clicked();
    void btnremove_clicked();
};