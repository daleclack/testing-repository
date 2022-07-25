#pragma once

#include <gtkmm.h>
#include "../cfgfile2/cfgfile.hh"

class CfgConvert : public Gtk::ApplicationWindow
{
public:
    CfgConvert();

private:
    // Config data
    conf_map config_data;

    // Open or save dialog
    Glib::RefPtr<Gtk::FileChooserNative> dialog;
    void dialog_response(int response_id);

    // Child widgets
    Gtk::Box main_box, btn_box;
    Gtk::Button btnopen, btnsave;

    // Treeview
    class ModelColumns : public Gtk::TreeModelColumnRecord
    {
    public:
        ModelColumns()
        {
            add(key);
            add(value);
        }
        Gtk::TreeModelColumn<Glib::ustring> key;
        Gtk::TreeModelColumn<Glib::ustring> value;
    };

    ModelColumns n_columns;
    Gtk::TreeView cfg_view;
    Glib::RefPtr<Gtk::ListStore> m_liststore;
    void treeview_init();

    // Signal Handlers
    void btnopen_clicked();
    void btnsave_clicked();
};