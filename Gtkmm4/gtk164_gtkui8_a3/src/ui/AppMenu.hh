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

// Button to renderer the apps
class AppButton : public Gtk::Button
{
public:
    AppButton()
        : app_box(Gtk::Orientation::VERTICAL, 5)
    {
        // Initalize the child widgets
        app_icon.set_pixel_size(48);
        set_has_frame(false);
        app_name.set_justify(Gtk::Justification::CENTER);
        app_name.set_width_chars(13);
        app_name.set_ellipsize(Pango::EllipsizeMode::END);

        // Add image and label to the button
        app_box.append(app_icon);
        app_box.append(app_name);
        set_child(app_box);
    }

    // Set the name and icon of the button, use icon name to set the icon
    void set_name_icon(Glib::ustring name, Glib::ustring icon)
    {
        app_icon.set_from_icon_name(icon);
        app_name.set_label(name);
    }

    // Set the name and icon of the button, use Gio::Icon to set the icon
    void set_name_icon(Glib::ustring name, Glib::RefPtr<Gio::Icon> icon)
    {
        // Use the C API due to the api leakage in gtkmm 4
        if (icon) // Some icon is not valid, use default icon
        {
            gtk_image_set_from_gicon(app_icon.gobj(), icon->gobj());
        }
        else
        {
            app_icon.set_from_icon_name("application-default-icon");
        }
        app_name.set_label(name);
    }

    // The external app should has its app info and set to external
    void set_app_info(Glib::RefPtr<Gio::AppInfo> info)
    {
        app_info = info;
        internal = false;
    }

    // The internal app should has its id and set to internal
    void set_app_id(guint id)
    {
        app_id = id;
        internal = true;
    }

    // Getters
    Glib::RefPtr<Gio::AppInfo> get_app_info() { return app_info; }
    bool is_internal() { return internal; }
    guint get_app_id() { return app_id; }

private:
    // Child widgets
    Gtk::Image app_icon;
    Gtk::Label app_name;
    Gtk::Box app_box;
    bool internal;
    guint app_id;
    Glib::RefPtr<Gio::AppInfo> app_info;
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
    Gtk::ScrolledWindow inner_scroll, ext_scroll;

    // List for the inner apps
    Glib::RefPtr<Gio::ListStore<AppItemIn>> inner_list;
    Glib::RefPtr<Gtk::SignalListItemFactory> inner_factory;
    Glib::RefPtr<Gtk::NoSelection> inner_selection;

    // Signal handlers for the inner view
    void inner_setup(const Glib::RefPtr<Gtk::ListItem> &item);
    void inner_bind(const Glib::RefPtr<Gtk::ListItem> &item);

    // List for the external apps
    std::vector<Glib::RefPtr<Gio::AppInfo>> app_list;
    Glib::RefPtr<Gio::ListStore<Gio::AppInfo>> ext_list;
    Glib::RefPtr<Gtk::SignalListItemFactory> ext_factory;
    Glib::RefPtr<Gtk::NoSelection> ext_selection;

    // Signal handlers for the external view
    void ext_setup(const Glib::RefPtr<Gtk::ListItem> &item);
    void ext_bind(const Glib::RefPtr<Gtk::ListItem> &item);
    void button_clicked(AppButton *btn);
};