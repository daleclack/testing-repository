#include "MyPrefs.hh"

MyPrefs::MyPrefs()
    : main_box(Gtk::ORIENTATION_VERTICAL, 10),
      views_box(Gtk::ORIENTATION_HORIZONTAL, 5),
      btnbox(Gtk::ORIENTATION_HORIZONTAL, 5)
{
    // Initalize Window
    set_title("Background Preferences");
    set_default_size(800, 450);

    // Initalize Stores
    folders_store = Gtk::ListStore::create(n_columns);
    folders_view.set_model(folders_store);
    images_store = Gtk::ListStore::create(n_columns);
    images_view.set_model(images_store);

    // Load Pixbufs
    auto pixbuf = Gdk::Pixbuf::create_from_resource("/org/gtk/daleclack/folder.svg");
    folder_pixbuf = pixbuf->scale_simple(24,24,Gdk::INTERP_BILINEAR);

    // Add Default Value for folders view
    auto row = *(folders_store->append());
    row[n_columns.m_col_path] = Glib::get_home_dir();
    row[n_columns.m_col_name] = "User's Home";
    row[n_columns.m_col_pixbuf] = folder_pixbuf;
    folders_view.append_column(" ",n_columns.m_col_pixbuf);
    folders_view.append_column("Folders", n_columns.m_col_name);

    row = *(folders_store->append());
    row[n_columns.m_col_path] = Glib::get_user_special_dir(Glib::USER_DIRECTORY_PICTURES);
    row[n_columns.m_col_name] = "User's Pictures Directory";
    row[n_columns.m_col_pixbuf] = folder_pixbuf;

    // Default Value for imags view
    row = *(images_store->append());
    row[n_columns.m_col_name] = "Test";
    images_view.append_column("Images", n_columns.m_col_name);

    // Add Views
    main_box.pack_start(views_box);
    sw_folders.add(folders_view);
    views_box.pack_start(sw_folders);
    sw_images.add(images_view);
    views_box.pack_start(sw_images);

    // Add Control Buttons
    btnadd.set_image_from_icon_name("list-add");
    btnadd.signal_clicked().connect(sigc::mem_fun(*this, &MyPrefs::btnadd_clicked));
    btnremove.set_image_from_icon_name("list-remove");
    btnbox.pack_start(btnadd, Gtk::PACK_SHRINK);
    btnbox.pack_start(btnremove, Gtk::PACK_SHRINK);
    main_box.pack_start(btnbox, Gtk::PACK_SHRINK);

    // Add Main Box to window
    const int margin_value = 15;
    main_box.set_margin_top(margin_value);
    main_box.set_margin_bottom(margin_value);
    main_box.set_margin_start(margin_value);
    main_box.set_margin_end(margin_value);
    add(main_box);
    show_all_children();
}

void MyPrefs::btnadd_clicked()
{
    // Create a dialog
    dialog = Gtk::FileChooserNative::create("Add a folder", *this,
                                            Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER, "OK", "Cancel");

    dialog->signal_response().connect(sigc::mem_fun(*this, &MyPrefs::dialog_response));

    dialog->show();
}

void MyPrefs::dialog_response(int response_id)
{
    if (response_id == Gtk::RESPONSE_ACCEPT)
    {
        // Get File Basename and Path
        auto file = dialog->get_file();
        auto basename = file->get_basename();
        auto filename = file->get_path();

        // Add to list
        auto row = *(folders_store->append());
        row[n_columns.m_col_path] = filename;
        row[n_columns.m_col_name] = basename;
        row[n_columns.m_col_pixbuf] = folder_pixbuf;

        file.reset();
    }
    dialog.reset();
}

void MyPrefs::btnremove_clicked() {}

void MyPrefs::set_background(Gtk::Image *back)
{
    background1 = back;
}
