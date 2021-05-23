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
        {add(m_col_id);add(m_col_text);add(m_col_percent);}
        Gtk::TreeModelColumn<int> m_col_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_text;
        Gtk::TreeModelColumn<int> m_col_percent;
    };

    int cols_count;
    ModelColumn m_columns;
    Gtk::TreeRow row;
    Glib::RefPtr<Gtk::ListStore> ref_liststore;
    Glib::RefPtr<Gtk::TreeSelection> ref_selection;

    //Child widgets
    Gtk::Box m_vbox;
    Gtk::ButtonBox m_buttonbox,m_btnbox_id,m_btnbox_text,m_btnbox_percent;
    Gtk::ScrolledWindow sw;
    Gtk::TreeView m_treeview;
    Gtk::Button btn_del;
    Gtk::Button btn_quit;
    Gtk::Label label_id,label_text,label_percent;
    Gtk::Entry entry_id,entry_text,entry_percent;
    Gtk::Button btn_add;
};