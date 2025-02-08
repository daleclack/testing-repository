#include "MsgDialog.hh"

MsgDialog::MsgDialog()
    : btn_ok("Ok")
{
    set_title("Message");

    // Add header bar
    set_titlebar(header_bar);
    header_bar.pack_end(btn_ok);
    header_bar.set_show_title_buttons(false);

    // Add message label
    set_child(label_msg);

    btn_ok.signal_clicked().connect([this] { close(); });
}

void MsgDialog::show_message(const Glib::ustring& message)
{
    label_msg.set_text(message);
    present();
}