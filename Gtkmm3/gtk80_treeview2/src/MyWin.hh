#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window{
public:
    MyWin();
    virtual ~MyWin();
protected:
    //Signal Handlers
    void on_btnquit_clicked();

    //TreeModel Columns
    class ModelColumn : public Gtk::TreeModelColumnRecord{
        public:
        ModelColumn()
        {add(m_col_num);add(m_col_text);}
        Gtk::TreeModelColumn<int> m_col_num;
        Gtk::TreeModelColumn<Glib::ustring> m_col_text;
    };

    ModelColumn m_columns;
    Gtk::TreeModel::Row row;
    Gtk::TreeModel::Row childrow;
    Glib::RefPtr<Gtk::TreeStore> ref_treestore;
    Glib::RefPtr<Gtk::TreeSelection> ref_selection;

    //Child widgets
    Gtk::Box m_vbox;
    Gtk::ButtonBox m_buttonbox;
    Gtk::ScrolledWindow sw;
    Gtk::TreeView m_treeview;
    Gtk::Button btn_quit;
};