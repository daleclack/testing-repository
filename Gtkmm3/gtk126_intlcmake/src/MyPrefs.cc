#include "MyPrefs.hh"
#include "winpe.xpm"
#include "../Gtk4/img7.xpm"
#include "image_types.hh"
#include "cfgfile/cfgfile.hh"
#include <iostream>
#include <fstream>
#include <glibmm/i18n.h>

MyPrefs::MyPrefs()
    : main_box(Gtk::ORIENTATION_VERTICAL, 10),
      views_box(Gtk::ORIENTATION_HORIZONTAL, 5),
      btnbox(Gtk::ORIENTATION_HORIZONTAL, 5),
      width(1024),
      height(576)
{
    /*Step 1: Initalize widget that without Gtk::Builder*/

    // Initalize Window
    set_title(_("Window Preferences"));
    set_default_size(800, 450);

    // Initalize Stores
    folders_store = Gtk::ListStore::create(n_columns);
    folders_store->set_default_sort_func(sigc::mem_fun(*this, &MyPrefs::sort_func));
    folders_store->set_sort_column(-1, Gtk::SORT_ASCENDING);
    folders_view.set_model(folders_store);
    folder_selection = folders_view.get_selection();
    folder_selection->signal_changed().connect(sigc::mem_fun(*this, &MyPrefs::folders_view_changed));

    images_store = Gtk::ListStore::create(n_columns);
    images_store->set_default_sort_func(sigc::mem_fun(*this, &MyPrefs::sort_func));
    images_store->set_sort_column(-1, Gtk::SORT_ASCENDING);
    images_view.set_model(images_store);
    image_selection = images_view.get_selection();
    image_selection->signal_changed().connect(sigc::mem_fun(*this, &MyPrefs::images_view_changed));

    // Load Pixbufs
    auto pixbuf = Gdk::Pixbuf::create_from_resource("/org/gtk/daleclack/folder.svg");
    folder_pixbuf = pixbuf->scale_simple(24, 24, Gdk::INTERP_BILINEAR);
    pixbuf.reset();
    pixbuf = Gdk::Pixbuf::create_from_resource("/org/gtk/daleclack/folder-images.svg");
    image_pixbuf = pixbuf->scale_simple(24, 24, Gdk::INTERP_BILINEAR);
    pixbuf.reset();
    pixbuf = Gdk::Pixbuf::create_from_resource("/org/gtk/daleclack/image_file.svg");
    imagefile_pixbuf = pixbuf->scale_simple(24, 24, Gdk::INTERP_BILINEAR);
    pixbuf.reset();

    // Add Default Value for folders view
    auto row = *(folders_store->append());
    row[n_columns.m_col_path] = "";
    row[n_columns.m_col_name] = _("Default Backgrounds");
    row[n_columns.m_col_pixbuf] = folder_pixbuf;
    row[n_columns.m_col_internal] = true;

    row = *(folders_store->append());
    row[n_columns.m_col_path] = Glib::get_home_dir();
    row[n_columns.m_col_name] = _("User's Home");
    row[n_columns.m_col_pixbuf] = folder_pixbuf;
    row[n_columns.m_col_internal] = false;

    row = *(folders_store->append());
    row[n_columns.m_col_path] = Glib::get_user_special_dir(Glib::USER_DIRECTORY_PICTURES);
    row[n_columns.m_col_name] = _("User's Pictures Directory");
    row[n_columns.m_col_pixbuf] = image_pixbuf;
    row[n_columns.m_col_internal] = false;

    // Append Column for the folders view
    folders_view.append_column(" ", n_columns.m_col_pixbuf);
    folders_view.append_column(_("Name"), n_columns.m_col_name);

    // Default Value for imags view
    default_folders_view();
    images_view.append_column(" ", n_columns.m_col_pixbuf);
    images_view.append_column(_("Images"), n_columns.m_col_name);

    // Add Views
    main_box.pack_start(views_box);
    sw_folders.add(folders_view);
    views_box.pack_start(sw_folders);
    sw_images.add(images_view);
    views_box.pack_start(sw_images);

    // Allow Selection
    has_selection = true;

    // Add Control Buttons
    btnadd.set_image_from_icon_name("list-add");
    btnadd.signal_clicked().connect(sigc::mem_fun(*this, &MyPrefs::btnadd_clicked));
    btnremove.set_image_from_icon_name("list-remove");
    btnremove.signal_clicked().connect(sigc::mem_fun(*this, &MyPrefs::btnremove_clicked));
    btnbox.pack_start(btnadd, Gtk::PACK_SHRINK);
    btnbox.pack_start(btnremove, Gtk::PACK_SHRINK);
    main_box.pack_start(btnbox, Gtk::PACK_SHRINK);

    // Add Main Box to window
    const int margin_value = 15;
    main_box.set_hexpand();
    main_box.set_vexpand();
    main_box.set_margin_top(margin_value);
    main_box.set_margin_bottom(margin_value);
    main_box.set_margin_start(margin_value);
    main_box.set_margin_end(margin_value);

    /*Step 2: Initalize widgets from glade xml file ('.ui' file)*/

    // Get Widgets for multi pages
    stackbuilder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/prefs_stack.ui");
    stackbuilder->get_widget("stack_box", stack_box);
    stackbuilder->get_widget("back_page", back_page);
    stackbuilder->get_widget("combo_default", combo_default);
    stackbuilder->get_widget("radio_default", radio_default);
    stackbuilder->get_widget("radio_custom", radio_custom);
    stackbuilder->get_widget("spin_width", spin_width);
    stackbuilder->get_widget("spin_height", spin_height);
    stackbuilder->get_widget("btnapply", btnapply);
    stackbuilder->get_widget("btnGet",btnGet);
    stackbuilder->get_widget("label_size",label_size);

    // Initalize radio buttons
    radio_default->set_active();
    radio_default->signal_toggled().connect(sigc::mem_fun(*this, &MyPrefs::radiobutton_toggled));
    radio_custom->signal_toggled().connect(sigc::mem_fun(*this, &MyPrefs::radiobutton_toggled));

    // Initalize other widgets
    btnapply->signal_clicked().connect(sigc::mem_fun(*this, &MyPrefs::btnapply_clicked));
    btnGet->signal_clicked().connect(sigc::mem_fun(*this,&MyPrefs::btnGet_clicked));

    // Initalize Label
    load_winsize_config();
    const char * cfgstr = _("Current Config");
    char * size_str = g_strdup_printf("%s: %d x %d", cfgstr, width, height);
    label_size->set_label(size_str);
    g_free(size_str);

    back_page->pack_start(main_box);
    add(*stack_box);
    show_all_children();
}

void MyPrefs::btnadd_clicked()
{
    // Create a dialog
    dialog = Gtk::FileChooserNative::create(_("Add a folder"), *this,
                                            Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER, _("OK"), _("Cancel"));

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

void MyPrefs::btnremove_clicked()
{
    // Get the selection and remove the selected item
    auto iter = folder_selection->get_selected();
    if (iter)
    {
        folders_store->erase(iter);
    }
}

void MyPrefs::folders_view_changed()
{
    // Get Selected Folder
    auto row = *(folder_selection->get_selected());
    if (row[n_columns.m_col_internal])
    {
        // The default folder
        default_folders_view();
    }
    else
    {
        // User defined folder
        std::string path = row[n_columns.m_col_path];
        update_images_view(path);
    }
}

void MyPrefs::default_folders_view()
{
    // Clear the store
    images_store->clear();

    // Add Default values
    auto row = *(images_store->append());
    row[n_columns.m_col_path] = ":1";
    row[n_columns.m_col_name] = "winpe.xpm";
    row[n_columns.m_col_internal] = true;
    row[n_columns.m_col_pixbuf] = imagefile_pixbuf;

    row = *(images_store->append());
    row[n_columns.m_col_path] = ":2";
    row[n_columns.m_col_name] = "img7.xpm";
    row[n_columns.m_col_internal] = true;
    row[n_columns.m_col_pixbuf] = imagefile_pixbuf;
}

int MyPrefs::sort_func(const Gtk::TreeModel::iterator &a, const Gtk::TreeModel::iterator &b)
{
    Glib::ustring name_a, name_b;

    // Get file names
    auto row_a = *(a);
    auto row_b = *(b);
    name_a = row_a[n_columns.m_col_name];
    name_b = row_b[n_columns.m_col_name];

    // Proform sort process
    if (name_a[0] != '.' && name_b[0] == '.')
    {
        return 1;
    }
    if (name_a[0] == '.' && name_b[0] != '.')
    {
        return -1;
    }
    else
    {
        return g_utf8_collate(name_a.c_str(), name_b.c_str());
    }
}

bool MyPrefs::icasecompare(const std::string &a, const std::string &b)
{
    if (a.length() == b.length())
    {
        return std::equal(a.begin(), a.end(), b.begin(),
                          [](char a, char b)
                          {
                              return tolower(a) == tolower(b);
                          });
    }
    else
    {
        return false;
    }
}

void MyPrefs::update_images_view(std::string &folder_path)
{
    // Unselect everything
    has_selection = false;

    // Clear the store
    images_store->clear();

    // Add Files into store
    try
    {
        Glib::Dir dir1(folder_path);
        bool is_dir, file_valid;
        Glib::ustring display_name;
        std::string filename, pathname;

        do
        {
            // Get File Name
            filename = dir1.read_name();

            // Get Path for a file
            pathname = Glib::build_filename(folder_path, filename);
            is_dir = Glib::file_test(pathname, Glib::FILE_TEST_IS_DIR);
            display_name = Glib::filename_to_utf8(filename);

            // Filter the file
            // Get Pattern of the file
            file_valid = false;
            size_t pos = filename.find_last_of('.');
            if (pos != std::string::npos)
            {
                std::string pattern = "*" + filename.substr(pos);
                for (int i = 0; supported_globs[i] != NULL; i++)
                {
                    std::string glob = std::string(supported_globs[i]);
                    if (icasecompare(glob, pattern))
                    {
                        file_valid = true;
                        break;
                    }
                }
            }

            if (!is_dir && file_valid)
            {
                // Add item to store
                auto row = *(images_store->append());
                row[n_columns.m_col_path] = pathname;
                row[n_columns.m_col_name] = display_name;
                row[n_columns.m_col_internal] = false;
                row[n_columns.m_col_pixbuf] = imagefile_pixbuf;
            }
        } while (filename != "");

        has_selection = true;
    }
    catch (Glib::Error &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

void MyPrefs::images_view_changed()
{
    // Set the background as selected
    if (has_selection)
    {
        auto row = *(image_selection->get_selected());
        if (row[n_columns.m_col_internal])
        {
            path = row[n_columns.m_col_path];
            switch (path[1])
            {
            case '1':
                set_background_internal(winpe);
                break;
            case '2':
                set_background_internal(img7);
                break;
            }
        }
        else
        {
            path = row[n_columns.m_col_path];
            set_background_file();
        }
    }
}

void MyPrefs::set_background_internal(const char *const *data)
{
    // Set a internal background
    auto pixbuf = Gdk::Pixbuf::create_from_xpm_data(data);
    auto sized = pixbuf->scale_simple(width, height, Gdk::INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(background1->gobj(), sized->gobj());
    pixbuf.reset();
    sized.reset();
    background_internal = true;
}

void MyPrefs::set_background_file()
{
    // Set Background from a file
    auto pixbuf = Gdk::Pixbuf::create_from_file(path);
    auto sized = pixbuf->scale_simple(width, height, Gdk::INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(background1->gobj(), sized->gobj());
    pixbuf.reset();
    sized.reset();
    background_internal = false;
}

void MyPrefs::update_background_size()
{}

void MyPrefs::set_background(Gtk::Image *back)
{
    background1 = back;
}

void MyPrefs::radiobutton_toggled()
{
    // Change sensitive state of buttons
    bool mode = radio_default->get_active();
    combo_default->set_sensitive(mode);
    spin_height->set_sensitive(!mode);
    spin_width->set_sensitive(!mode);
    btnGet->set_sensitive(!mode);
}

void MyPrefs::btnapply_clicked()
{
    // Get Config
    if (radio_default->get_active())
    {
        int mode = combo_default->get_active_row_number();
        switch (mode)
        {
        case 0:
            width = 640;
            height = 360;
            break;
        case 1:
            width = 800;
            height = 576;
            break;
        case 2:
            width = 1024;
            height = 576;
            break;
        case 3:
            width = 1280;
            height = 720;
            break;
        }
    }
    else
    {
        width = spin_width->get_value_as_int();
        height = spin_height->get_value_as_int();
    }

    // Open the file for configs
    std::fstream outfile;
    outfile.open("config", std::ios_base::out);
    if (outfile.is_open())
    {
        outfile << "width=" << width << std::endl;
        outfile << "height=" << height << std::endl;
        outfile.close();
    }
}

void MyPrefs::btnGet_clicked()
{
    //Get Current Window Size
    width = background1->get_width();
    height = background1->get_height();
    spin_width->set_value(width);
    spin_height->set_value(height);
}

void MyPrefs::load_winsize_config(){
    std::string height_str, width_str;

    // Read values from a file
    if (readCfgFile("config", "width", width_str) && readCfgFile("config", "height", height_str))
    {
        height = atoi(height_str.c_str());
        width = atoi(width_str.c_str());
    }
}

void MyPrefs::get_winsize_config(int &width1, int &height1)
{
    // Apply Config
    width1 = width;
    height1 = height;
}
