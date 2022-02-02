#pragma once

#include <gtkmm.h>
#include <string>

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
            add(m_col_internal);
        }
        Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> m_col_pixbuf;
        Gtk::TreeModelColumn<std::string> m_col_path;
        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
        Gtk::TreeModelColumn<bool> m_col_internal;
    };

    ModelColumns n_columns;
    Glib::RefPtr<Gtk::ListStore> folders_store, images_store;
    Glib::RefPtr<Gtk::TreeSelection> folder_selection, image_selection;
    bool has_selection;

private:
    // Widget for parent window
    Gtk::Image *background1;

    //Page switcher and another page
    Glib::RefPtr<Gtk::Builder> stackbuilder;
    Gtk::Box *stack_box, *back_page;

    // Child Widgets
    Gtk::TreeView folders_view, images_view;
    Gtk::ScrolledWindow sw_folders, sw_images;
    Gtk::Box main_box, views_box, btnbox;
    Gtk::Button btnadd, btnremove;

    // Folder Open Dialog
    Glib::RefPtr<Gdk::Pixbuf> folder_pixbuf, image_pixbuf, imagefile_pixbuf;
    Glib::RefPtr<Gtk::FileChooserNative> dialog;
    void dialog_response(int response_id);

    // Sort for ListStore
    int sort_func(const Gtk::TreeModel::iterator &a, const Gtk::TreeModel::iterator &b);
    bool icasecompare(const std::string &a, const std::string &b);

    // Signal Handlers
    void btnadd_clicked();
    void btnremove_clicked();
    void folders_view_changed();
    void images_view_changed();
    void default_folders_view();
    void update_images_view(std::string &folder_path);
    void set_background_internal(const char *const *data);
    void set_background_file(std::string &path);
};
