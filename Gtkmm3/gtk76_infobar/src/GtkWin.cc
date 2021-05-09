#include "GtkWin.hh"

GtkWin::GtkWin()
:vbox(Gtk::ORIENTATION_VERTICAL,5),
hbox(Gtk::ORIENTATION_HORIZONTAL,5),
btn_clear("Clear"),
btn_close("Close"){
    //Initalize window
    set_icon_name("org.gtk.daleclack");
    set_title("My Text Editor");
    set_default_size(400,300);
    //Initalize InfoBar
    auto content_area=dynamic_cast<Gtk::Container*>(m_infobar.get_content_area());
    if(content_area){
        content_area->add(info_label);
    }
    //Add a button
    m_infobar.add_button("OK",0);
    vbox.pack_start(m_infobar,Gtk::PACK_SHRINK);
    //Initalize textview
    sw.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    sw.add(m_textview);
    m_textbuffer=m_textview.get_buffer();
    vbox.pack_start(sw);
    //Connect Signals
    btn_close.signal_clicked().connect(sigc::mem_fun(*this,&GtkWin::close_clicked));
    btn_clear.signal_clicked().connect(sigc::mem_fun(*this,&GtkWin::clear_clicked));
    m_infobar.signal_response().connect(sigc::mem_fun(*this,&GtkWin::infobar_reponse));
    m_textbuffer->signal_changed().connect(sigc::mem_fun(*this,&GtkWin::buffer_changed));
    //Initalize layouts
    hbox.pack_end(btn_close,false,false);
    hbox.pack_end(btn_clear,false,false);
    vbox.pack_end(hbox,false,false);
    add(vbox);
    show_all();
    m_infobar.hide();
    btn_clear.set_sensitive(false);
}

void GtkWin::clear_clicked(){
    m_textbuffer->set_text("");
    info_label.set_label("Cleared the text");
    m_infobar.set_message_type(Gtk::MESSAGE_INFO);
    m_infobar.show();
}

void GtkWin::close_clicked(){
    hide();
}

void GtkWin::infobar_reponse(int response){
    info_label.set_label("");
    m_infobar.hide();
}

void GtkWin::buffer_changed(){
    btn_clear.set_sensitive(m_textbuffer->size() > 0);
}

GtkWin::~GtkWin(){

}