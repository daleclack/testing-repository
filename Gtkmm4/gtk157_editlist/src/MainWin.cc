#include "MainWin.hh"

MainWin::MainWin()
    : main_box(Gtk::Orientation::HORIZONTAL, 5),
      lists_box(Gtk::Orientation::VERTICAL, 5),
      drop_box(Gtk::Orientation::VERTICAL, 5),
      btn_box(Gtk::Orientation::HORIZONTAL, 5),
      drop_frame("Dropdown widget"),
      list_frame("Items List"),
      btn_add("Add Item"),
      btn_remove("Remove Item"),
      btn_save("Save config"),
      btn_show("Show items")
{
    // Initalize window
    set_icon_name("org.gtk.daleclack");
    set_default_size(600, 400);
    set_title("Dynamic Dropdown test");

    // Add overlay widget
    drop_box.set_halign(Gtk::Align::CENTER);
    drop_box.set_valign(Gtk::Align::CENTER);
    drop_overlay.add_overlay(drop_box);
    drop_frame.set_child(drop_overlay);

    // Add widgets for the left side
    btn_get.set_label("Show");
    drop_box.append(dropdown);
    drop_box.append(btn_get);

    // Create List for column View
    main_list = Gio::ListStore<ModelColumns>::create();

    // The list for dropdown to select should has no selection
    selection = Gtk::NoSelection::create(main_list);
    main_column_view.set_model(selection);

    // Add items
    load_config();

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
    btn_get.signal_clicked().connect(sigc::mem_fun(*this, &MainWin::btnget_clicked));
    btn_save.signal_clicked().connect(sigc::mem_fun(*this, &MainWin::btnsave_clicked));

    // Add List widget
    // Scrolled window for listview widget
    m_sw.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_sw.set_expand();
    m_sw.set_halign(Gtk::Align::FILL);
    m_sw.set_valign(Gtk::Align::FILL);
    m_sw.set_child(main_column_view);
    lists_box.append(m_sw);

    // Entry and buttons
    btn_box.set_halign(Gtk::Align::CENTER);
    btn_box.append(btn_add);
    btn_box.append(btn_remove);
    btn_box.append(btn_show);
    btn_box.append(btn_save);
    lists_box.append(btn_box);
    list_frame.set_child(lists_box);

    // Append the frames to the main box
    main_box.append(drop_frame);
    main_box.append(list_frame);
    set_child(main_box);
}

void MainWin::load_config()
{
    // Open json file and try to parse
    std::fstream json_file;
    json_file.open("config.json", std::ios_base::in);
    json data = json::parse(json_file);

    // Get vectors from json
    if (!data.empty())
    {
        // Put data to the GListStore
        str_vec branch_vec = data["branches"];
        str_vec version_vec = data["versions"];
        for (int i = 0; i < branch_vec.size(); i++)
        {
            main_list->append(ModelColumns::create(branch_vec[i].c_str(),
                                                   version_vec[i].c_str()));
        }
    }
    else
    {
        main_list->append(ModelColumns::create("Longterm", "5.14"));
        main_list->append(ModelColumns::create("Stable", "9.1"));
        main_list->append(ModelColumns::create("Develop", "10.0"));
    }
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
    auto item1 = main_list->get_item(pos);
    entry->set_text(item1->get_version_str());
    Glib::Binding::bind_property(item1->property_version(), entry->property_text(),
                                 Glib::Binding::Flags::BIDIRECTIONAL);
}

void MainWin::btnadd_clicked()
{
    // Append a item to the list
    main_list->append(ModelColumns::create("", ""));
}

void MainWin::btnremove_clicked()
{
    // Get Position of item
    auto pos = main_list->get_n_items() - 1;

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

void MainWin::btnget_clicked()
{
    // Get Selected item index
    auto index = dropdown.get_selected();

    // Get item in the store
    auto item = main_list->get_item(index);

    // Get Version string
    auto ver_str = item->get_version_str();

    std::cout << ver_str << std::endl;
}

void MainWin::btnsave_clicked()
{
    // Get items count for the list
    auto length = main_list->get_n_items();
    str_vec branch_vec, version_vec;

    // Push item strings to the vectors
    for (int i = 0; i < length; i++)
    {
        auto item = main_list->get_item(i);
        const char *temp1 = item->get_branch_str().c_str();
        branch_vec.push_back(temp1);
        const char *temp2 = item->get_version_str().c_str();
        version_vec.push_back(temp2);
    }

    // Create a json file
    json data = json::parse(R"({
        "Note":"Generated, do not edit it!",
        "branches":[],
        "versions":[]
    })");

    // Creata file to save json data
    std::fstream json_file;
    json_file.open("config.json", std::ios_base::out);

    // Save config when file creates
    if (json_file.is_open())
    {
        data["branches"] = branch_vec;
        data["versions"] = version_vec;
        json_file << data;
    }
    json_file.close();
}
