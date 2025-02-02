#include "AppMenu.hh"

AppMenu::AppMenu()
{
    // Update the inner menu
    inner_list = Gio::ListStore<AppItemIn>::create();
    inner_list->append(AppItemIn::create("24Game", "24game", 0));
    inner_list->append(AppItemIn::create("About", "btnabout", 1));
    inner_list->append(AppItemIn::create("Calculator", "calcapp", 2));
    inner_list->append(AppItemIn::create("Drawing", "drawing_app", 3));
    inner_list->append(AppItemIn::create("MyFinder", "file-app", 4));
    inner_list->append(AppItemIn::create("Guess Game", "game", 5));
    inner_list->append(AppItemIn::create("Image Viewer", "image_app", 6));
    inner_list->append(AppItemIn::create("Preferences", "my_prefs", 7));
    inner_list->append(AppItemIn::create("Run App", "myrunner", 8));
    inner_list->append(AppItemIn::create("Media Player", "media-app", 9));
    inner_list->append(AppItemIn::create("MineSweeper", "mines_app", 10));

    // Initialize the inner grid view
    inner_selection = Gtk::NoSelection::create(inner_list);
    inner_factory = Gtk::SignalListItemFactory::create();
    inner_factory->signal_setup().connect(sigc::mem_fun(*this, &AppMenu::inner_setup));
    inner_factory->signal_bind().connect(sigc::mem_fun(*this, &AppMenu::inner_bind));
    inner_view.set_model(inner_selection);
    inner_view.set_factory(inner_factory);
    // inner_view.set_max_columns(5);
    inner_view.set_min_columns(3);

    // Update the outer menu

    // Add inner grid view to the box
    inner_scroll.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
    inner_scroll.set_hexpand(true);
    inner_scroll.set_vexpand(true);
    inner_scroll.set_child(inner_view);
    append(inner_scroll);
    set_hexpand(true);
    set_vexpand(true);
}

void AppMenu::inner_setup(const Glib::RefPtr<Gtk::ListItem> &item)
{
    auto button = Gtk::make_managed<AppButton>();
    item->set_child(*button);
}

void AppMenu::inner_bind(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Get the position of the item
    auto position = item->get_position();
    if (position == GTK_INVALID_LIST_POSITION)
    {
        return;
    }

    // Get the item
    auto item1 = inner_list->get_item(position);
    auto button = dynamic_cast<AppButton *>(item->get_child());
    button->set_name_icon(item1->get_name(), item1->get_icon());
}
