#include "MyWin.hh"

MyWin::MyWin(BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade)
:Gtk::Window(cobject),
ref_builder(ref_Glade)
{
    // Initalize Window
    set_icon_name("org.gtk.daleclack");

    // Get Widgets
    ref_builder->get_widget("picker_box",picker_box);
    ref_builder->get_widget("panel_box",panel_box);
    ref_builder->get_widget("ref_box",ref_box);

    // Add Child Widgets
    color_picker.bind_parent_win(this);
    picker_box->pack_start(color_picker);

    color_panel = ColorPanel::create();
    color_panel->set_halign(Gtk::ALIGN_CENTER);
    color_panel->set_valign(Gtk::ALIGN_CENTER);
    panel_box->pack_start(*color_panel);

    show_all_children();
}

MyWin * MyWin::create()
{
    MyWin * window = nullptr;

    auto builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/window.ui");
    builder->get_widget_derived("main_window",window);

    return window;
}
