#pragma once

#include <gtkmm.h>

enum class ViewMode{
    MODE_ICON,
    MODE_LIST
};

class FileWindow : public Gtk::Window{
public:
    FileWindow();
    ~FileWindow();
private:
    //List Model
    class ModelColumns : public Gtk::TreeModelColumnRecord{
    public:
        ModelColumns(){
            add(m_col_path);add(m_col_display_name);add(m_col_pixbuf);add(m_col_is_dir);
        }
        Gtk::TreeModelColumn<Glib::ustring> m_col_path;
        Gtk::TreeModelColumn<Glib::ustring> m_col_display_name;
        Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> m_col_pixbuf;
        Gtk::TreeModelColumn<bool> m_col_is_dir;
    };

    ModelColumns columns;
    Gtk::TreeView m_treeview;
    Gtk::IconView m_iconview;
    Glib::RefPtr<Gtk::TreeSelection> m_selection;
    Glib::RefPtr<Gtk::ListStore> m_liststore;

    //File Proprties
    Glib::RefPtr<Gdk::Pixbuf> file_pixbuf;
    Glib::RefPtr<Gdk::Pixbuf> folder_pixbuf;
    Glib::ustring parent_str,tmp_str;
    ViewMode view_mode;

    //Child Widgets
    Gtk::Box vbox,btnbox,menubox;
    Gtk::Toolbar m_toolbar,m_viewbar;
    Gtk::ToolButton up_button,home_button,new_button,delete_button;
    Gtk::ToolItem view_item,menu_item;
    Gtk::ScrolledWindow m_sw;
    Gtk::Button view_button;
    Gtk::MenuButton menubtn;
    Gtk::Stack stack;
    Gtk::Popover popover;
    Gtk::CheckButton show_hidden;
    Gtk::InfoBar m_infobar;
    Gtk::Label info_label;

    //Initalize Functions
    void fill_store();
    void initalize_views();
    int sort_func(const Gtk::TreeModel::iterator &a,const Gtk::TreeModel::iterator &b);

    //Signal Handlers
    void item_activated(const Gtk::TreePath &path);
    void row_activated(const Gtk::TreePath &path,Gtk::TreeViewColumn * sel_column);
    void btnup_clicked();
    void btnhome_clicked();
    void btnnew_clicked();
    void btndel_clicked();
    void btnview_clicked();
    void infobar_response(int response_id);
};