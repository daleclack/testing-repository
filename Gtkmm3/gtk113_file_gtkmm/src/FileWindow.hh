#pragma once

#include <gtkmm.h>

enum class ViewMode{
    MODE_ICON,
    MODE_GRID
};

class FileWindow : public Gtk::Window{
public:
    FileWindow();
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

    Gtk::TreeView m_treeview;
    Gtk::IconView m_iconview;
    Glib::RefPtr<Gtk::TreeSelection> m_selection;
    Glib::RefPtr<Gtk::ListStore> m_liststore;

    //File Proprties
    Glib::RefPtr<Gdk::Pixbuf> file_pixbuf;
    Glib::RefPtr<Gdk::Pixbuf> folder_pixbuf;
    Glib::ustring parent_str;
    ViewMode view_mode;

    //Child Widgets
    Gtk::Box vbox,btnbox;
    Gtk::Toolbar m_toolbar,m_viewbar;
    Gtk::ToolButton up_button,home_button,new_button,delete_button;
    Gtk::ToolItem view_item,menu_item;
    Gtk::ScrolledWindow m_sw;
    Gtk::Button view_button;
    Gtk::MenuButton menubtn;

    //Signal Handlers
};