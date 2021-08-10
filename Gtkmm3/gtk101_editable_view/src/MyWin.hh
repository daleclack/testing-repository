#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window{
public:
    MyWin();
private:

    //Model Columns
    class ModelColumns : public Gtk::TreeModelColumnRecord{
    public:
        ModelColumns()
        {add(m_col_id); add(m_col_name); add(m_col_number);}

        Gtk::TreeModelColumn<int> m_col_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
        Gtk::TreeModelColumn<Glib::ustring> m_col_number;
    };

    ModelColumns m_columns;

    Glib::RefPtr<Gtk::ListStore> ref_liststore;
    Glib::RefPtr<Gtk::TreeSelection> selection;
    
    //Child Widgets
    Gtk::TreeView m_treeview;
    Gtk::Box main_box;
    Gtk::ScrolledWindow scrolled;
    Gtk::Label m_label;
    Gtk::Button btn_exit;

    //Signal Handlers
    void selection_changed();
};