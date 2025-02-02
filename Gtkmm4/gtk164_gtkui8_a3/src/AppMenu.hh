#pragma once

#include <gtkmm.h>

// List item for inner app
class AppItemIn : public Glib::Object
{
public:
    // Bind properties
    AppItemIn(Glib::ustring name, Glib::ustring icon, guint id)
    {
        app_name = name;
        app_icon = icon;
        app_id = id;
    }

    // Create a new item
    static Glib::RefPtr<AppItemIn> create(Glib::ustring name, Glib::ustring icon, guint id)
    {
        return Glib::make_refptr_for_instance<AppItemIn>(new AppItemIn(name, icon, id));
    }

    // Getters
    Glib::ustring get_name() { return app_name; }
    Glib::ustring get_icon() { return app_icon; }
    guint get_id() { return app_id; }

private:
    // Properties
    Glib::ustring app_name;
    Glib::ustring app_icon;
    guint app_id;
};

// List item for external app
class AppItemExt : public Glib::Object
{
};

class AppMenu : public Gtk::Box
{
public:
    AppMenu();

private:
    // Child widgets
    Gtk::GridView inner_view, ext_view;
    Gtk::Stack menu_stack;
    Gtk::StackSwitcher menu_switcher;

    // List for the inner apps
    Glib::RefPtr<Gio::ListStore<AppItemIn>> inner_list;

    // List for the external apps
    Glib::RefPtr<Gio::ListStore<AppItemExt>> ext_list;
};