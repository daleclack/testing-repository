#include "MainWin.hh"

MainWin::MainWin()
    : main_box(Gtk::Orientation::HORIZONTAL, 5),
      lists_box(Gtk::Orientation::VERTICAL, 5),
      drop_frame("Dropdown widget"),
      list_frame("Items List"),
      btn_add("Add Item"),
      btn_remove("Remove Item"),
      btn_show("Show items")
{
    // Initalize window
    set_icon_name("org.gtk.daleclack");
    set_default_size(600, 400);
    set_title("Dynamic Dropdown test");

    // Add overlay widget
    dropdown.set_halign(Gtk::Align::CENTER);
    dropdown.set_valign(Gtk::Align::CENTER);
    drop_overlay.add_overlay(dropdown);
    drop_frame.set_child(drop_overlay);

    // Create List for column View
    main_list = Gio::ListStore<ModelColumns>::create();
    selection = Gtk::SingleSelection::create(main_list);
    main_column_view.set_model(selection);

    // Add items
    main_list->append(ModelColumns::create("Longterm", "5.14"));
    main_list->append(ModelColumns::create("Stable", "9.1"));
    main_list->append(ModelColumns::create("Develop", "10.0"));

    // Create string list
    dropdown.set_model(main_list);

    // Add factory for dropdown
    drop_factory = Gtk::SignalListItemFactory::create();
    drop_factory->signal_bind().connect(sigc::mem_fun(*this, &MainWin::bind_drop));
    drop_factory->signal_setup().connect(sigc::mem_fun(*this, &MainWin::setup_drop));
    dropdown.set_factory(drop_factory);
    dropdown.set_list_factory(drop_factory);

    // Add a factory to the branch column
    branch_factory = Gtk::SignalListItemFactory::create();
    branch_factory->signal_bind().connect(sigc::mem_fun(*this, &MainWin::bind_branch));
    branch_factory->signal_setup().connect(sigc::mem_fun(*this, &MainWin::setup_branch));
    branch_column = Gtk::ColumnViewColumn::create("Branch", branch_factory);
    main_column_view.append_column(branch_column);

    // Add a factory to the version column
    version_factory = Gtk::SignalListItemFactory::create();
    version_factory->signal_bind().connect(sigc::mem_fun(*this, &MainWin::bind_version));
    version_factory->signal_setup().connect(sigc::mem_fun(*this, &MainWin::setup_version));
    version_column = Gtk::ColumnViewColumn::create("Version", version_factory);
    main_column_view.append_column(version_column);

    // Link Signal for buttons
    btn_add.signal_clicked().connect(sigc::mem_fun(*this, &MainWin::btnadd_clicked));
    btn_remove.signal_clicked().connect(sigc::mem_fun(*this, &MainWin::btnremove_clicked));
    btn_show.signal_clicked().connect(sigc::mem_fun(*this, &MainWin::btnshow_clicked));

    // Add List widget
    // Scrolled window for listview widget
    m_sw.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_sw.set_expand();
    m_sw.set_halign(Gtk::Align::FILL);
    m_sw.set_valign(Gtk::Align::FILL);
    m_sw.set_child(main_column_view);
    lists_box.append(m_sw);

    // Entry and buttons
    btn_add.set_halign(Gtk::Align::CENTER);
    btn_remove.set_halign(Gtk::Align::CENTER);
    btn_show.set_halign(Gtk::Align::CENTER);
    // lists_box.append(item_entry);
    lists_box.append(btn_add);
    lists_box.append(btn_remove);
    lists_box.append(btn_show);
    list_frame.set_child(lists_box);

    // Append the frames to the main box
    main_box.append(drop_frame);
    main_box.append(list_frame);
    set_child(main_box);
}

void MainWin::setup_drop(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Set label for item
    item->set_child(*Gtk::make_managed<Gtk::Label>());
}

void MainWin::bind_drop(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Get position
    auto pos = item->get_position();

    // Get label widget
    auto label = dynamic_cast<Gtk::Label *>(item->get_child());
    if (!label)
    {
        return;
    }

    // Set text to the label
    auto item1 = main_list->get_item(pos);
    label->set_text(item1->get_branch_str());
}

void MainWin::setup_branch(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Set label for item
    item->set_child(*Gtk::make_managed<Gtk::Entry>());
}

void MainWin::bind_branch(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Get position
    auto pos = item->get_position();

    // Get Entry
    auto entry = dynamic_cast<Gtk::Entry *>(item->get_child());
    if (!entry)
    {
        return;
    }

    // Bind text
    // auto item1 = dynamic_cast<ModelColumns *>(item.get());
    auto item1 = main_list->get_item(pos);
    entry->set_text(item1->get_branch_str());
    Glib::Binding::bind_property(item1->property_branch(), entry->property_text(),
                                 Glib::Binding::Flags::BIDIRECTIONAL);
}

void MainWin::setup_version(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Set label for item
    item->set_child(*Gtk::make_managed<Gtk::Entry>());
}

void MainWin::bind_version(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Get position
    auto pos = item->get_position();

    // Get Entry
    auto entry = dynamic_cast<Gtk::Entry *>(item->get_child());
    if (!entry)
    {
        return;
    }

    // Bind text
    // auto item1 = dynamic_cast<ModelColumns *>(item.get());
    auto item1 = main_list->get_item(pos);
    entry->set_text(item1->get_version_str());
    Glib::Binding::bind_property(item1->property_version(), entry->property_text(),
                                 Glib::Binding::Flags::BIDIRECTIONAL);
}

void MainWin::btnadd_clicked()
{
    // Append a item to the list
    main_list->append(ModelColumns::create(" ", " "));
}

void MainWin::btnremove_clicked()
{
    // Get Position of item
    auto pos = selection->get_selected();

    // Remove item
    main_list->remove(pos);
}

void MainWin::btnshow_clicked()
{
    // Show all items and sync the main list to drop down
    auto length = main_list->get_n_items();

    for (int i = 0; i < length; i++)
    {
        auto item = main_list->get_item(i);
        std::cout << item->get_branch_str().c_str() << " "
                  << item->get_version_str().c_str() << std::endl;
    }
}
