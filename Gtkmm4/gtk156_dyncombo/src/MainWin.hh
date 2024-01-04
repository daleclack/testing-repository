#pragma once

#include "../json_nlohmann/json.hpp"
#include <vector>
#include <gtkmm.h>

using json = nlohmann::json;
typedef std::vector<std::string> str_vec;

// Main Window Class
class MainWin : public Gtk::ApplicationWindow
{
public:
    MainWin();

private:
    // Use StringList for dropdown and json file
    Glib::RefPtr<Gtk::StringList> dropdown_list;
    Glib::RefPtr<Gtk::SingleSelection> selection;

    // Factory to renderer
    Glib::RefPtr<Gtk::SignalListItemFactory> factory;
    void setup_label(const Glib::RefPtr<Gtk::ListItem> &item);
    void bind_label(const Glib::RefPtr<Gtk::ListItem> &item);

    // Child widgets
    Gtk::DropDown dropdown;
    Gtk::Overlay drop_overlay;
    Gtk::Box main_box, lists_box;
    Gtk::Frame drop_frame, list_frame;
    Gtk::ScrolledWindow m_sw;
    Gtk::ListView main_list_view;
    Gtk::Entry item_entry;
    Gtk::Button btn_add, btn_remove;

    // Signal Handlers
    void btnadd_clicked();
    void btnremove_clicked();
};