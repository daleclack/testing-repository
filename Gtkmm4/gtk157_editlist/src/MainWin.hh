#pragma once

#include "../json_nlohmann/json.hpp"
#include <vector>
#include <gtkmm.h>
#include <iostream>
#include <fstream>

using json = nlohmann::json;
typedef std::vector<std::string> str_vec;

// ModelColumns class
class ModelColumns : public Glib::Object
{
public:
    // Create a new object
    static Glib::RefPtr<ModelColumns> create(Glib::ustring &branch1, Glib::ustring &version1)
    {
        return Glib::make_refptr_for_instance<ModelColumns>(new ModelColumns(branch1, version1));
    }
    static Glib::RefPtr<ModelColumns> create(const char *branch1, const char *version1)
    {
        Glib::ustring temp_branch(branch1), temp_version(version1);
        return Glib::make_refptr_for_instance<ModelColumns>(new ModelColumns(temp_branch, temp_version));
    }

    // Get Value of branch and version
    Glib::ustring get_branch_str()
    {
        return branch_prep.get_value();
    }

    Glib::ustring get_version_str()
    {
        return version_prep.get_value();
    }

    // Get PropertyProxy
    Glib::PropertyProxy<Glib::ustring> property_branch()
    {
        return branch_prep.get_proxy();
    }

    Glib::PropertyProxy<Glib::ustring> property_version()
    {
        return version_prep.get_proxy();
    }

private:
    // Use Glib::Property to bind
    Glib::Property<Glib::ustring> branch_prep, version_prep;

protected:
    // Register type and initalize properties
    ModelColumns(Glib::ustring branch, Glib::ustring version)
        : Glib::ObjectBase(typeid(ModelColumns)),
          Glib::Object(),
          branch_prep(*this, "branch", branch),
          version_prep(*this, "version", version)
    {
    }
};

// Main Window Class
class MainWin : public Gtk::ApplicationWindow
{
public:
    MainWin();

private:
    // Main list object for branchs and versions
    Glib::RefPtr<Gio::ListStore<ModelColumns>> main_list;
    Glib::RefPtr<Gtk::NoSelection> selection;

    // Factory to renderer string for dropdown
    Glib::RefPtr<Gtk::SignalListItemFactory> drop_factory;
    void setup_drop(const Glib::RefPtr<Gtk::ListItem> &item);
    void bind_drop(const Glib::RefPtr<Gtk::ListItem> &item);

    // Factory to renderer branch string
    Glib::RefPtr<Gtk::ColumnViewColumn> branch_column;
    Glib::RefPtr<Gtk::SignalListItemFactory> branch_factory;
    void setup_branch(const Glib::RefPtr<Gtk::ListItem> &item);
    void bind_branch(const Glib::RefPtr<Gtk::ListItem> &item);

    // Factory to renderer version string
    Glib::RefPtr<Gtk::ColumnViewColumn> version_column;
    Glib::RefPtr<Gtk::SignalListItemFactory> version_factory;
    void setup_version(const Glib::RefPtr<Gtk::ListItem> &item);
    void bind_version(const Glib::RefPtr<Gtk::ListItem> &item);

    // Child widgets
    Gtk::DropDown dropdown;
    Gtk::Overlay drop_overlay;
    Gtk::Box main_box, lists_box, drop_box, btn_box;
    Gtk::Frame drop_frame, list_frame;
    Gtk::ScrolledWindow m_sw;
    Gtk::ListView main_list_view;
    Gtk::ColumnView main_column_view;
    // Gtk::Entry item_entry;
    Gtk::Button btn_get, btn_add, btn_remove,
        btn_save, btn_show;

    void load_config();

    // Signal Handlers
    void btnadd_clicked();
    void btnremove_clicked();
    void btnshow_clicked();
    void btnget_clicked();
    void btnsave_clicked();
};
