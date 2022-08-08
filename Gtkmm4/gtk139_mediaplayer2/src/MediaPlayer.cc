#include "MediaPlayer.hh"
#include "../json_nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <vector>

using json = nlohmann::json;

MediaPlayer::MediaPlayer()
    : vbox(Gtk::Orientation::VERTICAL, 5),
      btnbox(Gtk::Orientation::HORIZONTAL, 5)
{
    // Set icon and title
    set_title("Gtk4 media player");
    set_icon_name("org.gtk.daleclack");
    set_default_size(400, 500);

    // Add widgets
    video1.set_size_request(400, 225);
    vbox.append(video1);

    // Controllers
    btnadd.set_image_from_icon_name("list-add");
    btnremove.set_image_from_icon_name("list-remove");
    btnload.set_image_from_icon_name("go-up");
    btnsave.set_image_from_icon_name("document-save");
    btnbox.append(btnadd);
    btnbox.append(btnremove);
    btnbox.append(btnload);
    btnbox.append(btnsave);
    vbox.append(btnbox);
    btnadd.signal_clicked().connect(sigc::mem_fun(*this, &MediaPlayer::btnadd_clicked));
    btnremove.signal_clicked().connect(sigc::mem_fun(*this, &MediaPlayer::btnremove_clicked));
    btnload.signal_clicked().connect(sigc::mem_fun(*this, &MediaPlayer::btnload_clicked));
    btnsave.signal_clicked().connect(sigc::mem_fun(*this, &MediaPlayer::btnsave_clicked));

    // List of media files
    scroll_win.set_hexpand();
    scroll_win.set_vexpand();
    scroll_win.set_child(treeview);
    vbox.append(scroll_win);

    // Initalize treeview
    store = Gtk::ListStore::create(n_columns);
    treeview.set_model(store);
    treeview.append_column("File Name", n_columns.file_name);
    selection = treeview.get_selection();

    // Add vbox to the window
    set_child(vbox);
}

void MediaPlayer::btnadd_clicked()
{
    // Create Native dialog
    dialog = Gtk::FileChooserNative::create("Open Media File", *this,
                                            Gtk::FileChooser::Action::OPEN, "OK", "Cancel");

    dialog->signal_response().connect(sigc::mem_fun(*this, &MediaPlayer::dialog_response));

    // Add Filter
    auto filter = Gtk::FileFilter::create();
    filter->add_pattern("*");
    filter->set_name("All Files");
    dialog->add_filter(filter);

    dialog->show();
}

void MediaPlayer::dialog_response(int response_id)
{
    if (response_id == Gtk::ResponseType::ACCEPT)
    {
        // Get Path and basename
        auto file = dialog->get_file();
        auto filename = file->get_basename();
        auto path = file->get_path();

        // Append the item
        auto row = *(store->append());
        row[n_columns.file_name] = filename;
        row[n_columns.file_path] = path;

        file.reset();
    }
    dialog.reset();
}

void MediaPlayer::btnremove_clicked()
{
    auto row = selection->get_selected();
    store->erase(row);
}

void MediaPlayer::btnload_clicked()
{
    // Clear current store
    store->clear();

    // Get data
    std::ifstream playlist("playlist.json");
    if (playlist.is_open())
    {
        // Get data
        json data = json::parse(playlist);
        std::vector<std::string> name_tmp = data["name"];
        std::vector<std::string> path_tmp = data["path"];

        // Initalize Liststore
        if (name_tmp.size() != path_tmp.size())
        {
            std::cout << "Data Invaild!" << std::endl;
        }
        else
        {
            for (int i = 0; i < name_tmp.size(); i++)
            {
                // Append the item
                auto row = *(store->append());
                row[n_columns.file_name] = name_tmp[i];
                row[n_columns.file_path] = path_tmp[i];
            }
        }
    }
}

void MediaPlayer::btnsave_clicked()
{
    
}
