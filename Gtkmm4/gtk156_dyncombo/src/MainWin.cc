#include "MainWin.hh"

MainWin::MainWin()
    : main_box(Gtk::Orientation::HORIZONTAL, 5),
    lists_box(Gtk::Orientation::VERTICAL, 5),
    drop_frame("Dropdown widget"),
    list_frame("Items List"),
    btn_add("Add Item"),
    btn_remove("Remove Item")
{
    // Initalize window
    set_icon_name("org.gtk.daleclack");
    set_default_size(600, 400);
    set_title("Dynamic Dropdown test");

    // Add overlay widget
    dropdown.set_halign(Gtk::Align::CENTER);
    dropdown.set_valign(Gtk::Align::CENTER);
    drop_overlay.add_overlay(dropdown);
    drop_frame.set_child(drop_overlay);

    

    // Add List widget
    // Scrolled window for listview widget
    m_sw.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_sw.set_expand();
    m_sw.set_halign(Gtk::Align::FILL);
    m_sw.set_valign(Gtk::Align::FILL);
    m_sw.set_child(main_list_view);
    lists_box.append(m_sw);

    // Entry and buttons
    btn_add.set_halign(Gtk::Align::CENTER);
    btn_remove.set_halign(Gtk::Align::CENTER);
    lists_box.append(item_entry);
    lists_box.append(btn_add);
    lists_box.append(btn_remove);
    list_frame.set_child(lists_box);

    // Append the frames to the main box
    main_box.append(drop_frame);
    main_box.append(list_frame);
    set_child(main_box);
}

void MainWin::btnadd_clicked()
{
    Glib::ustring entry_str;

    // Get String from entry
    entry_str = item_entry.get_text();

    // Append text to the list
    if (!entry_str.empty())
    {
        dropdown_list->append(entry_str);
    }
}

void MainWin::btnremove_clicked()
{
}