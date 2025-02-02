#include "MyPanel.hh"

MyPanel::MyPanel()
{
    // Get the panel widget
    builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/cambalache/mypanel.ui");
    panel_box = builder->get_widget<Gtk::Box>("panel_box");
    btnstart = builder->get_widget<Gtk::Button>("btnstart");
    apps_stack = builder->get_widget<Gtk::Stack>("apps_stack");
    apps_box = builder->get_widget<Gtk::Box>("apps_box");

    // Connect signal handlers
    btnstart->signal_clicked().connect(sigc::mem_fun(*this, &MyPanel::btnstart_clicked));

    // Add apps view
    apps_box->append(app_menu);
}

void MyPanel::btnstart_clicked()
{
    // Change the visible page in the stack
    auto child_name = apps_stack->get_visible_child_name();
    if (child_name == "page1")
    {
        apps_stack->set_visible_child("page2");
    }
    else
    {
        apps_stack->set_visible_child("page1");
    }
}
