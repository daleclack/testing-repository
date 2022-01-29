#include "MyPrefs.hh"

MyPrefs::MyPrefs()
:main_box(Gtk::ORIENTATION_VERTICAL,10),
views_box(Gtk::ORIENTATION_HORIZONTAL,5),
btnbox(Gtk::ORIENTATION_HORIZONTAL,5)
{
    //Initalize Window
    set_title("Background Preferences");
    set_default_size(800,450);

    //Initalize Stores
    folders_store = Gtk::ListStore::create(n_columns);
    folders_view.set_model(folders_store);
    images_store = Gtk::ListStore::create(n_columns);
    images_view.set_model(images_store);

    //Add Default Value for folders view
    auto row = *(folders_store->append());
    row[n_columns.m_col_name] = Glib::get_home_dir();
    folders_view.append_column("Folders",n_columns.m_col_name);

    //Default Value for imags view
    row = *(images_store->append());
    row[n_columns.m_col_name] = "Test";
    images_view.append_column("Images",n_columns.m_col_name);

    //Add Views
    main_box.pack_start(views_box);
    sw_folders.add(folders_view);
    views_box.pack_start(sw_folders);
    sw_images.add(images_view);
    views_box.pack_start(sw_images);

    //Add Control Buttons
    main_box.pack_start(btnbox,Gtk::PACK_SHRINK);

    //Add Main Box to window
    const int margin_value = 15;
    main_box.set_margin_top(margin_value);
    main_box.set_margin_bottom(margin_value);
    main_box.set_margin_start(margin_value);
    main_box.set_margin_end(margin_value);
    add(main_box);
    show_all_children();
}

void MyPrefs::set_background(Gtk::Image *back){
    background1 = back;
}
