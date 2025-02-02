#include "AppMenu.hh"
#include <iostream>

AppMenu::AppMenu()
{
    // Initalize the main box
    set_orientation(Gtk::Orientation::VERTICAL);

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

    // Add inner grid view to the scrolled window
    inner_scroll.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
    inner_scroll.set_hexpand(true);
    inner_scroll.set_vexpand(true);
    inner_scroll.set_child(inner_view);
    inner_scroll.set_has_frame(false);

    // Update the outer menu
    ext_list = Gio::ListStore<Gio::AppInfo>::create();
    auto app_list = Gio::AppInfo::get_all();
    for (int i = 0; i < app_list.size(); ++i)
    {
        ext_list->append(app_list[i]);
    }
    ext_selection = Gtk::NoSelection::create(ext_list);
    ext_factory = Gtk::SignalListItemFactory::create();
    ext_factory->signal_setup().connect(sigc::mem_fun(*this, &AppMenu::ext_setup));
    ext_factory->signal_bind().connect(sigc::mem_fun(*this, &AppMenu::ext_bind));
    ext_view.set_model(ext_selection);
    ext_view.set_factory(ext_factory);
    ext_view.set_min_columns(3);

    // Add outer grid view to the scrolled window
    ext_scroll.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
    ext_scroll.set_hexpand(true);
    ext_scroll.set_vexpand(true);
    ext_scroll.set_child(ext_view);
    ext_scroll.set_has_frame(false);

    // Add a Gtk::Stack to show the to pages
    menu_stack.set_transition_type(Gtk::StackTransitionType::SLIDE_LEFT_RIGHT);
    menu_stack.add(inner_scroll, "Integrated", "Integrated");
    menu_stack.add(ext_scroll, "External", "External");
    menu_switcher.set_stack(menu_stack);
    menu_switcher.set_halign(Gtk::Align::CENTER);

    // Connect signals
    // ext_view.signal_activate().connect(sigc::mem_fun(*this, &AppMenu::ext_activate));

    append(menu_stack);
    append(menu_switcher);
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

    // Get the item and update the button
    auto item1 = inner_list->get_item(position);
    auto button = dynamic_cast<AppButton *>(item->get_child());
    button->set_name_icon(item1->get_name(), item1->get_icon());
    button->signal_clicked().connect(sigc::bind(
        sigc::mem_fun(*this, &AppMenu::button_clicked), button));
    button->set_app_id(position);
}

void AppMenu::ext_setup(const Glib::RefPtr<Gtk::ListItem> &item)
{
    auto button = Gtk::make_managed<AppButton>();
    item->set_child(*button);
}

void AppMenu::ext_bind(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Get the position of the item
    auto position = item->get_position();
    if (position == GTK_INVALID_LIST_POSITION)
    {
        return;
    }

    // Get the item and update the button
    auto item1 = ext_list->get_item(position);
    auto button = dynamic_cast<AppButton *>(item->get_child());
    button->set_name_icon(item1->get_name(), item1->get_icon());
    button->signal_clicked().connect(sigc::bind(
        sigc::mem_fun(*this, &AppMenu::button_clicked), button));
    button->set_app_info(item1);
}

void AppMenu::button_clicked(AppButton *btn)
{
    if (btn->is_internal())
    {
        std::cout << "Internal App: " << btn->get_app_id() << std::endl;
    }else{
        auto app_info = btn->get_app_info();
        app_info->launch(NULL);
    }
}
