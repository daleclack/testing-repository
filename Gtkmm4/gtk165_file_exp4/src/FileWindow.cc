#include "FileWindow.hh"
#include "config.hh"
#include <iostream>

FileWindow::FileWindow()
    : main_box(Gtk::Orientation::VERTICAL, 5),
      place_box(Gtk::Orientation::HORIZONTAL, 5),
      views_box(Gtk::Orientation::HORIZONTAL, 5)
{
    // Initalize window
    set_default_size(640, 400);

    // Create a directory list for the home folder.
    auto file = Gio::File::create_for_path(Glib::get_home_dir());
    dir_list = Gtk::DirectoryList::create(
        "standard::name,standard::display-name,standard::icon,standard::size,standard::content-type", file);

    dir_selection = Gtk::SingleSelection::create(dir_list);

    // Initalize the view
    main_view.set_model(dir_selection);

    // Create factory for file icons
    icon_factory = Gtk::SignalListItemFactory::create();
    icon_factory->signal_setup().connect(sigc::mem_fun(*this, &FileWindow::icon_setup));
    icon_factory->signal_bind().connect(sigc::mem_fun(*this, &FileWindow::icon_bind));
    auto column_icons = Gtk::ColumnViewColumn::create(" ", icon_factory);
    main_view.append_column(column_icons);

    // Create factory for file names
    name_factory = Gtk::SignalListItemFactory::create();
    name_factory->signal_setup().connect(sigc::mem_fun(*this, &FileWindow::name_setup));
    name_factory->signal_bind().connect(sigc::mem_fun(*this, &FileWindow::name_bind));
    auto column_names = Gtk::ColumnViewColumn::create("Name", name_factory);
    main_view.append_column(column_names);

    // Create factory for file types
    type_factory = Gtk::SignalListItemFactory::create();
    type_factory->signal_setup().connect(sigc::mem_fun(*this, &FileWindow::type_setup));
    type_factory->signal_bind().connect(sigc::mem_fun(*this, &FileWindow::type_bind));
    auto column_types = Gtk::ColumnViewColumn::create("Type", type_factory);
    main_view.append_column(column_types);

    // Create factory for file sizes
    size_factory = Gtk::SignalListItemFactory::create();
    size_factory->signal_setup().connect(sigc::mem_fun(*this, &FileWindow::size_setup));
    size_factory->signal_bind().connect(sigc::mem_fun(*this, &FileWindow::size_bind));
    auto column_sizes = Gtk::ColumnViewColumn::create("Size", size_factory);
    main_view.append_column(column_sizes);

    // Places store
    places_list = Gtk::StringList::create();
    places_list->append(Glib::get_home_dir());
    places_list->append(Glib::get_user_special_dir(Glib::UserDirectory::DESKTOP));
    places_list->append(Glib::get_user_special_dir(Glib::UserDirectory::DOCUMENTS));
    places_list->append(Glib::get_user_special_dir(Glib::UserDirectory::DOWNLOAD));
    places_list->append(Glib::get_user_special_dir(Glib::UserDirectory::MUSIC));
    places_list->append(Glib::get_user_special_dir(Glib::UserDirectory::PICTURES));
    places_list->append(Glib::get_user_special_dir(Glib::UserDirectory::VIDEOS));

    // Add the places sidebar
    places_selection = Gtk::SingleSelection::create(places_list);
    places_view.set_model(places_selection);
    places_scroller.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
    places_scroller.set_child(places_view);

    // Create factory for places
    places_factory = Gtk::SignalListItemFactory::create();
    places_factory->signal_setup().connect(sigc::mem_fun(*this, &FileWindow::places_setup));
    places_factory->signal_bind().connect(sigc::mem_fun(*this, &FileWindow::places_bind));
    places_view.set_factory(places_factory);

    // Add topbar for the places
    btn_up.set_icon_name("go-up");
    btn_add.set_icon_name("list-add");
    btn_del.set_icon_name("list-remove");
    place_box.append(btn_up);
    place_box.append(btn_add);
    place_box.append(btn_del);
    place_box.append(place_entry);
    place_entry.set_hexpand();
    place_entry.set_text(Glib::get_home_dir());

    // Add the view to the windos
    main_scroller.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    main_scroller.set_child(main_view);
    main_scroller.set_expand();
    main_box.append(place_box);
    main_box.append(views_box);
    views_box.append(places_scroller);
    views_box.append(main_scroller);
    set_child(main_box);

    // Initalize dialogs
    new_dialog.set_transient_for(*this);
    msg_dialog.set_transient_for(*this);

    // Connect signals
    main_view.signal_activate().connect(sigc::mem_fun(*this, &FileWindow::folder_item_activated));
    btn_add.signal_clicked().connect(sigc::mem_fun(*this, &FileWindow::btnadd_clicked));
    btn_del.signal_clicked().connect(sigc::mem_fun(*this, &FileWindow::btndel_clicked));
    btn_up.signal_clicked().connect(sigc::mem_fun(*this, &FileWindow::btnup_clicked));
}

void FileWindow::btnadd_clicked()
{
    auto file = dir_list->get_file();
    auto path = file->get_path();
    new_dialog.show_dialog(path);
}

void FileWindow::btndel_clicked()
{
    msg_dialog.show_message("Delete failed");
}

void FileWindow::btnup_clicked()
{
    // Get parent file and path
    auto file = dir_list->get_file();
    auto path = file->get_path();
    if (path.length() > 1)
    {
        auto parent = file->get_parent();

        // Update directory list
        dir_list->set_file(parent);

        // Update place entry
        auto path = parent->get_path();
        place_entry.set_text(path);

        // Reset file
        file.reset();
    }
}

void FileWindow::placebtn_clicked(FileBtn *btn)
{
    auto path = btn->file_path;
    dir_list->set_file(Gio::File::create_for_path(path));
    place_entry.set_text(path);
}

void FileWindow::folder_item_activated(guint pos)
{
    // Get file info
    auto info = std::dynamic_pointer_cast<Gio::FileInfo>(
        dir_selection->get_selected_item());
    auto content_type = info->get_content_type();
    if (content_type == "inode/directory")
    {
        // Get Current path
        auto file = dir_list->get_file();
        std::string path;

        // Update path
        if (is_windows())
        {
            path = file->get_path() + '\\' + info->get_name();
        }
        else
        {
            path = file->get_path();
            if (path.length() > 1)
            {
                path += '/';
            }
            path += info->get_name();
        }

        // Update directory list
        auto new_file = Gio::File::create_for_path(path);
        dir_list->set_file(new_file);

        file.reset();
        place_entry.set_text(path);
        // std::cout << "Opening folder: " << path << std::endl;
    }
}

void FileWindow::places_setup(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Create and initalize a button
    auto btn = Gtk::make_managed<FileBtn>(" ");
    btn->set_halign(Gtk::Align::START);
    auto label = dynamic_cast<Gtk::Label *>(btn->get_child());
    label->set_ellipsize(Pango::EllipsizeMode::END);
    label->set_max_width_chars(20);
    item->set_child(*btn);
}

void FileWindow::places_bind(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Get child widget
    auto btn = dynamic_cast<FileBtn *>(item->get_child());

    // Get position
    auto position = item->get_position();
    auto path = places_list->get_string(position);
    size_t end_pos;

    if (is_windows())
    {
        end_pos = path.find_last_of("\\");
    }
    else
    {
        end_pos = path.find_last_of("/");
    }

    auto display_name = path.substr(end_pos + 1);
    btn->set_label(display_name);
    btn->file_path = path;
    btn->signal_clicked().connect(sigc::bind(
        sigc::mem_fun(*this, &FileWindow::placebtn_clicked), btn));
}

// Setup and bind the icon
void FileWindow::icon_setup(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Add a image
    auto image = Gtk::make_managed<Gtk::Image>();
    image->set_pixel_size(24);
    item->set_child(*image);
}

void FileWindow::icon_bind(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Get child widget
    auto image = dynamic_cast<Gtk::Image *>(item->get_child());

    // Get icon
    auto file_info = std::dynamic_pointer_cast<Gio::FileInfo>(item->get_item());

    // Use C API to set the icon
    gtk_image_set_from_gicon(image->gobj(), file_info->get_icon()->gobj());
}

void FileWindow::name_setup(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Create and initalize a label
    auto label = Gtk::make_managed<Gtk::Label>();
    label->set_ellipsize(Pango::EllipsizeMode::END);
    label->set_max_width_chars(20);
    label->set_halign(Gtk::Align::START);
    item->set_child(*label);
}

void FileWindow::name_bind(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Get child widget
    auto label = dynamic_cast<Gtk::Label *>(item->get_child());

    // Get File info
    auto file_info = std::dynamic_pointer_cast<Gio::FileInfo>(item->get_item());
    auto name = file_info->get_name();

    // Set the label
    label->set_text(name);
}

void FileWindow::size_setup(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Create and initalize a label
    auto label = Gtk::make_managed<Gtk::Label>();
    label->set_ellipsize(Pango::EllipsizeMode::END);
    label->set_max_width_chars(20);
    label->set_halign(Gtk::Align::START);
    item->set_child(*label);
}

void FileWindow::size_bind(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Get child widget
    auto label = dynamic_cast<Gtk::Label *>(item->get_child());

    // Get File info
    auto file_info = std::dynamic_pointer_cast<Gio::FileInfo>(item->get_item());
    auto size = file_info->get_size();

    // Set the label
    label->set_text(std::to_string(size));
}

void FileWindow::type_setup(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Create and initalize a label
    auto label = Gtk::make_managed<Gtk::Label>();
    label->set_ellipsize(Pango::EllipsizeMode::END);
    label->set_max_width_chars(20);
    label->set_halign(Gtk::Align::START);
    item->set_child(*label);
}

void FileWindow::type_bind(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Get child widget
    auto label = dynamic_cast<Gtk::Label *>(item->get_child());

    // Get File info
    auto file_info = std::dynamic_pointer_cast<Gio::FileInfo>(item->get_item());
    auto type = file_info->get_content_type();

    // Set the label
    label->set_text(type);
}