#include "NewDialog.hh"

NewDialog::NewDialog()
    : btn_ok("OK"), btn_cancel("Cancel")

{
    set_title("New Folder");

    // Initalize headerbar
    set_titlebar(header);
    header.pack_end(btn_ok);
    header.pack_start(btn_cancel);
    header.set_show_title_buttons(false);

    set_child(entry_name);

    // Connect signals
    entry_name.signal_activate().connect([this]
                                         { btnok_clicked(); });
    btn_cancel.signal_clicked().connect([this]
                                        { close(); });
    btn_ok.signal_clicked().connect(sigc::mem_fun(*this, &NewDialog::btnok_clicked));
}

void NewDialog::show_dialog(std::string& path)
{
    info_path = path;
    present();
}

void NewDialog::btnok_clicked()
{
    auto name = entry_name.get_text();
    info_path += "/" + name;
    g_mkdir_with_parents(info_path.c_str(), 0777);
    close();
}