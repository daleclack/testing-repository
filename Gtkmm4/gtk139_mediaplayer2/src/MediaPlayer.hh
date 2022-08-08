#pragma once

#include <gtkmm.h>

class MediaPlayer : public Gtk::ApplicationWindow
{
public:
    MediaPlayer();

private:
    // Main video widget
    Gtk::Video video1;

    // Model Columns
    class ModelColumns : public Gtk::TreeModelColumnRecord
    {
    public:
        ModelColumns()
        {
            add(file_name);
            add(file_path);
        }
        Gtk::TreeModelColumn<std::string> file_name;
        Gtk::TreeModelColumn<std::string> file_path;
    };

    ModelColumns n_columns;
    Glib::RefPtr<Gtk::ListStore> store;

    // Listview widget
    Gtk::TreeView treeview;
    Glib::RefPtr<Gtk::TreeSelection> selection;

    // Main widgets
    Gtk::Box vbox, btnbox;
    Gtk::ScrolledWindow scroll_win;
    Gtk::Button btnadd, btnremove, btnload, btnsave;

    // FileChooser
    Glib::RefPtr<Gtk::FileChooserNative> dialog;
    void dialog_response(int response_id);

    // Signal Handlers
    void btnadd_clicked();
    void btnremove_clicked();
    void btnload_clicked();
    void btnsave_clicked();
};