#pragma once

#include <gtkmm.h>
#include "../cfgfile2/cfgfile.hh"

class MyWin : public Gtk::Window{
public:

    MyWin();

private:

    //Model Columns
    class ModelColumns : public Gtk::TreeModelColumnRecord{
    public:
        ModelColumns()
        {add(m_col_key); add(m_col_value); }

        Gtk::TreeModelColumn<Glib::ustring> m_col_key;
        Gtk::TreeModelColumn<Glib::ustring> m_col_value;
    };

    ModelColumns m_columns;

    Glib::RefPtr<Gtk::ListStore> ref_liststore;
    Glib::RefPtr<Gtk::TreeSelection> selection;
    
    //Child Widgets
    Gtk::TreeView m_treeview;
    Gtk::Box main_box,btn_box;
    Gtk::ScrolledWindow scrolled;
    Gtk::Label m_label;
    Gtk::Button btn_load,btn_save,btn_exit;

    Glib::RefPtr<Gtk::FileChooserNative> dialog;
    
    //Keys and values for config
    conf_map my_configs;

    //Signal Handlers
    void selection_changed();
    void btnload_clicked();
    void btnsave_clicked();
    void dialog_response(int response_id);
    void dialog_save_response(int response_id);

};