#include "MyStack.hh"

MyStack::MyStack()
    : login_box(Gtk::Orientation::VERTICAL, 5),
    login_label("dale"),
    login_button("Login")
{
    // Add the builder
    m_builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/cambalache/overlaywin.ui");

    // Get the stack widget and child widgets
    m_stack = m_builder->get_widget<Gtk::Stack>("main_stack");
    login_page = m_builder->get_widget<Gtk::Overlay>("login_page");
    main_page = m_builder->get_widget<Gtk::Box>("main_page");

    // Add background image for login page
    login_background.set_resource("/org/gtk/daleclack/winpe.png");
    login_page->set_child(login_background);
    login_background.set_hexpand(true);
    login_background.set_vexpand(true);
    login_background.set_keep_aspect_ratio(false);

    // Create login page widgets
    login_image.set_pixel_size(48);
    login_image.set_from_icon_name("My_GtkUI");
    login_button.set_has_frame(false);
    login_box.append(login_image);
    login_box.append(login_label);
    login_box.append(login_button);
    login_box.set_halign(Gtk::Align::CENTER);
    login_box.set_valign(Gtk::Align::CENTER);
    login_page->add_overlay(login_box);
}