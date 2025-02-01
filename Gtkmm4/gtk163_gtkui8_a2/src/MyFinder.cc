#include "MyFinder.hh"

MyFinder::MyFinder()
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
}