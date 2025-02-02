#include "MainWin.hh"

MainWin::MainWin(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_builder1)
    : Glib::ObjectBase("MainWin"),
      Gtk::ApplicationWindow(cobject),
      ref_builder(ref_builder1)
{
    set_default_icon_name("My_GtkUI");
    // Get widgets from the builder
    main_overlay = ref_builder->get_widget<Gtk::Overlay>("main_overlay");
    main_background = ref_builder->get_widget<Gtk::Picture>("main_background");

    // Default background image
    main_background->set_keep_aspect_ratio(false);
    main_background->set_hexpand(true);
    main_background->set_vexpand(true);
    main_background->set_resource("/org/gtk/daleclack/shizuku.png");

    // Add stack to the window
    Gtk::Stack *stack = main_stack.m_stack;
    stack->set_halign(Gtk::Align::FILL);
    stack->set_valign(Gtk::Align::FILL);
    main_overlay->add_overlay(*stack);
}

MainWin *MainWin::create()
{
    // Create a new MainWin instance and return it.
    MainWin *main_win = nullptr;

    // Create a new Builder object and load the interface file.
    auto builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/cambalache/mainwin.ui");

    // Get the MainWin object from the builder and return it.
    main_win = Gtk::Builder::get_widget_derived<MainWin>(builder, "mainwin");
    return main_win;
}