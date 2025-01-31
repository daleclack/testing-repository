#include "MyPanel.hh"

MyPanel::MyPanel()
{
    // Get the panel widget
    builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/cambalache/mypanel.ui");
    panel_box = builder->get_widget<Gtk::Box>("panel_box");
}