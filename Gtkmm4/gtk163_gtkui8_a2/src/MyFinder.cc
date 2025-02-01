#include "MyFinder.hh"
#include <ctime>

MyFinder::MyFinder()
:title_label("My GtkUI")
{
    // Create the GtkBuilder object
    builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/cambalache/findermenu.ui");

    // Get the child widgets
    menu_stack = builder->get_widget<Gtk::Stack>("menu_stack");
    inner_stack = builder->get_widget<Gtk::Stack>("inner_stack");
    inner_switcher = builder->get_widget<Gtk::StackSwitcher>("inner_switcher");

    // Set the stack switcher to control the inner_stack
    inner_switcher->set_stack(*inner_stack); // Note the use of inner_stack, not menu_stack in this line

    // Default stack page for debug
    menu_stack->set_visible_child("page2");

    // Update button icons
    btn_audio.set_has_frame(false);
    btn_audio.set_icon_name("finder_audio");
    btn_battery.set_has_frame(false);
    btn_battery.set_icon_name("finder-battery");
    btn_computer.set_has_frame(false);
    btn_computer.set_icon_name("finder-computer");
    btn_search.set_has_frame(false);
    btn_search.set_icon_name("finder-find");
    btn_wifi.set_has_frame(false);
    btn_wifi.set_icon_name("finder-wifi");
    btn_menu.set_has_frame(false);
    btn_menu.set_icon_name("open-menu");
    btn_time.set_has_frame(false);
    btn_time.set_label("2025/2/1 19:42:00");
    space_label.set_hexpand(true);
    space_label.set_halign(Gtk::Align::FILL);

    // Add widgets to the menu box
    menu_box.append(title_label);
    menu_box.append(space_label);
    menu_box.append(btn_audio);
    menu_box.append(btn_battery);
    menu_box.append(btn_computer);
    menu_box.append(btn_search);
    menu_box.append(btn_wifi);
    menu_box.append(btn_time);
    menu_box.append(btn_menu);
}