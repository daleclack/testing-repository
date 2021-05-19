#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window{
public:
    MyWin();
    virtual ~MyWin();
protected:
    //Signal Handlers
    void on_btnquit_clicked();
    void btndel_clicked();
    void btnadd_clicked();

    //TreeModel Columns
    class ModelColumn : public Gtk::TreeModelColumnRecord{
        public:
        ModelColumn()
        {add(m_col_text);}
        Gtk::TreeModelColumn<Glib::ustring> m_col_text;
    };

    ModelColumn m_columns;
    Gtk::TreeRow row;
    Glib::RefPtr<Gtk::ListStore> ref_liststore;
    Glib::RefPtr<Gtk::TreeSelection> ref_selection;

    //Child widgets
    Gtk::Box m_vbox;
    Gtk::ButtonBox m_buttonbox;
    Gtk::ScrolledWindow sw;
    Gtk::TreeView m_treeview;
    Gtk::Button btn_del;
    Gtk::Button btn_quit;
    Gtk::Entry m_entry;
    Gtk::Button btn_add;
};