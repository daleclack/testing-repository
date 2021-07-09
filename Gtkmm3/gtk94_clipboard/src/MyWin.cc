#include "MyWin.hh"

MyWin::MyWin()
:vbox(Gtk::ORIENTATION_VERTICAL,5),
hbox(Gtk::ORIENTATION_HORIZONTAL,5),
btnbox(Gtk::ORIENTATION_VERTICAL,5),
btn_copy("Copy"),
btn_paste("Paste")
{
    //Initalize Window
    set_default_size(800,450);
    set_icon_name("org.gtk.daleclack");
    
    //Initalize Text Buffers
    buffer1=textview1.get_buffer();
    buffer2=textview2.get_buffer();
    buffer1->signal_changed().connect(sigc::mem_fun(*this,&MyWin::buffer1_changed));

    //Pack Widgets
    sw1.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    sw2.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    sw1.add(textview1);
    sw2.add(textview2);
    btnbox.set_valign(Gtk::ALIGN_CENTER);
    btnbox.pack_start(btn_copy,Gtk::PACK_SHRINK);
    btnbox.pack_start(btn_paste,Gtk::PACK_SHRINK);
    hbox.pack_start(sw1);
    hbox.pack_start(btnbox,Gtk::PACK_SHRINK);
    hbox.pack_start(sw2);
    
    btn_copy.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btncopy_clicked));
    btn_paste.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnpaste_clicked));

    //Disable Buttons
    btn_copy.set_sensitive(false);
    btn_paste.set_sensitive(false);

    //A InfoBar
    infobar.add_button("OK",Gtk::RESPONSE_OK);
    infobar.signal_response().connect(sigc::mem_fun(*this,&MyWin::infobar_response));
    infobox=dynamic_cast<Gtk::Box*>(infobar.get_content_area());
    infobox->pack_start(label1);
    vbox.pack_start(infobar,Gtk::PACK_SHRINK);

    //Show everything
    vbox.pack_start(hbox);
    add(vbox);
    show_all_children();
    infobar.hide();
}

void MyWin::buffer1_changed(){
    //When the text changed,enable the copy button
    btn_copy.set_sensitive();
}

void MyWin::btncopy_clicked(){
    //Get Text
    Glib::ustring text;
    text=buffer1->get_text();

    //Get Clipboard and set text
    auto refClipboard=Gtk::Clipboard::get();
    refClipboard->set_text(text);
    btn_paste.set_sensitive();

    //Show InfoBar
    label1.set_label("The Text is copyed");
    infobar.show();
}

void MyWin::btnpaste_clicked(){
    //Get ClipBoard
    auto refClipboard=Gtk::Clipboard::get();
    refClipboard->request_text(sigc::mem_fun(*this,&MyWin::clipboard_receive));

    //Show InfoBar
    label1.set_label("The Text is Pasted");
    infobar.show();
}

void MyWin::clipboard_receive(const Glib::ustring &text){
    buffer2->set_text(text);
}

void MyWin::infobar_response(int response){
    infobar.hide();
}
