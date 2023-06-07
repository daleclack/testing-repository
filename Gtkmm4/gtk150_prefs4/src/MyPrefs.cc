#include "MyPrefs.hh"

MyPrefs::MyPrefs()
    : main_box(Gtk::Orientation::VERTICAL, 5),
      views_box(Gtk::Orientation::HORIZONTAL, 5),
      buttons_box(Gtk::Orientation::HORIZONTAL, 5)
{
    // Initalize the window
    set_icon_name("org.gtk.daleclack");
    set_default_size(800, 450);

    // Create List Store for folders_view
    folder_store = Gio::ListStore<MyItem>::create();
    folder_select = Gtk::SingleSelection::create(folder_store);
    folders_view.set_model(folder_select);

    // Fill the store
    folder_store->append(MyItem::create("User's home folder", Glib::get_home_dir()));
    folder_store->append(MyItem::create("test2", "test3"));

    // Initalize factory to renderer the object
    folder_image_factory = Gtk::SignalListItemFactory::create();
    folder_image_factory->signal_setup().connect(sigc::mem_fun(*this, &MyPrefs::folder_image_setup));
    folder_image_factory->signal_bind().connect(sigc::mem_fun(*this, &MyPrefs::folder_image_bind));
    folder_string_factory = Gtk::SignalListItemFactory::create();
    folder_string_factory->signal_setup().connect(sigc::mem_fun(*this, &MyPrefs::folder_string_setup));
    folder_string_factory->signal_bind().connect(sigc::mem_fun(*this, &MyPrefs::folder_string_bind));

    // Create Columns and append
    folder_image_column = Gtk::ColumnViewColumn::create(" ", folder_image_factory);
    folder_string_column = Gtk::ColumnViewColumn::create("Names", folder_string_factory);
    folders_view.append_column(folder_image_column);
    folders_view.append_column(folder_string_column);

    // Add timer to scan
    selection_timer = Glib::signal_timeout().connect(sigc::mem_fun(*this, &MyPrefs::timeout_func), 16);

    // Pack widgets
    folders_view.set_expand();
    images_view.set_expand();
    views_box.append(folders_view);
    views_box.append(images_view);
    main_box.append(views_box);
    main_box.append(buttons_box);
    set_child(main_box);
}

void MyPrefs::folder_image_setup(const Glib::RefPtr<Gtk::ListItem> &item){
    // Add image to show
    item->set_child(image_folder);
}

void MyPrefs::folder_image_bind(const Glib::RefPtr<Gtk::ListItem> &item){
    // Get the image widget
    auto image = dynamic_cast<Gtk::Image*>(item->get_child());

    // Bind the value of item
    auto value = Glib::RefPtr<MyItem>(dynamic_cast<MyItem*>(item->get_item().get()));

    // Set image
    image->set_from_icon_name(value->icon_name);
}

void MyPrefs::folder_string_setup(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Add a label to the item
    item->set_child(label_folder);
}

void MyPrefs::folder_string_bind(const Glib::RefPtr<Gtk::ListItem> &item)
{
    // Get the label
    auto label = dynamic_cast<Gtk::Label*>(item->get_child());

    // Bind the value of item
    auto value = Glib::RefPtr<MyItem>(dynamic_cast<MyItem*>(item->get_item().get()));

    // Set the label
    label->set_label(value->file_name);
}

bool MyPrefs::timeout_func(){
    // Refresh the view for folders
    // Refresh the view for images
    return true;
}
