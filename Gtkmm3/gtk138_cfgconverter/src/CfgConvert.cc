#include "CfgConvert.hh"
#include <iostream>
#include "../json_nlohmann/json.hpp"

using json = nlohmann::json;

CfgConvert::CfgConvert()
    : main_box(Gtk::ORIENTATION_HORIZONTAL, 5),
      btn_box(Gtk::ORIENTATION_VERTICAL, 5),
      btnopen("Open cfg file"),
      btnsave("Save json file")
{
    // Initalize window
    set_default_size(800, 450);
    set_title("Simple Config File Converter");
    set_icon_name("org.gtk.daleclack");

    // Create List Store
    m_liststore = Gtk::ListStore::create(n_columns);
    cfg_view.append_column("Key", n_columns.key);
    cfg_view.append_column("Value", n_columns.value);
    cfg_view.set_model(m_liststore);

    // Pack Buttons
    btn_box.pack_start(btnopen, Gtk::PACK_SHRINK);
    btn_box.pack_start(btnsave, Gtk::PACK_SHRINK);
    btn_box.set_valign(Gtk::ALIGN_CENTER);
    btnopen.signal_clicked().connect(sigc::mem_fun(*this, &CfgConvert::btnopen_clicked));
    btnsave.signal_clicked().connect(sigc::mem_fun(*this, &CfgConvert::btnsave_clicked));

    // Pack Widgets
    main_box.pack_start(cfg_view);
    main_box.pack_start(btn_box, Gtk::PACK_SHRINK);
    add(main_box);
    show_all_children();
}

void CfgConvert::btnsave_clicked()
{
    // Create dialog
    dialog = Gtk::FileChooserNative::create("Open Config File", *this,
                                            Gtk::FILE_CHOOSER_ACTION_SAVE, "OK", "Cancel");
    // Create filters
    auto filter_any = Gtk::FileFilter::create();
    filter_any->add_pattern("*");
    filter_any->set_name("Any Config File");

    dialog->add_filter(filter_any);

    // Link Signal and show the dialog
    dialog->signal_response().connect(sigc::mem_fun(*this, &CfgConvert::dialog_response));
    dialog->show();
}

void CfgConvert::btnopen_clicked()
{
    // Create dialog
    dialog = Gtk::FileChooserNative::create("Open Config File", *this,
                                            Gtk::FILE_CHOOSER_ACTION_OPEN, "OK", "Cancel");
    // Create filters
    auto filter_any = Gtk::FileFilter::create();
    filter_any->add_pattern("*");
    filter_any->set_name("Any Config File");

    dialog->add_filter(filter_any);

    // Link Signal and show the dialog
    dialog->signal_response().connect(sigc::mem_fun(*this, &CfgConvert::dialog_response));
    dialog->show();
}

void CfgConvert::dialog_response(int response)
{
    if (response == Gtk::RESPONSE_ACCEPT)
    {
        // Use action to execute the save and open action
        auto action = dialog->get_action();

        // Get Filename
        auto file = dialog->get_file();
        auto path = file->get_path();
        std::fstream outfile;
        json data;
        switch (action)
        {
        case Gtk::FILE_CHOOSER_ACTION_OPEN:
            // Read data to std::map and show
            if (readCfgFile(path, config_data))
            {
                treeview_init();
            }
            break;
        case Gtk::FILE_CHOOSER_ACTION_SAVE:
            // Save data to json file
            data = json(config_data);
            outfile.open(path, std::ios_base::out);
            if (outfile.is_open())
            {
                outfile << data;
            }
            outfile.close();
            break;
        default:
            std::cout << "Error!" << std::endl;
        }
        file.reset();
    }
    dialog.reset();
}

void CfgConvert::treeview_init()
{
    // Clear the data
    m_liststore->clear();

    // Append data
    auto mite = config_data.begin();
    for (; mite != config_data.end(); mite++)
    {
        auto row = *(m_liststore->append());
        row[n_columns.key] = mite->first;
        row[n_columns.value] = mite->second;
    }
}
