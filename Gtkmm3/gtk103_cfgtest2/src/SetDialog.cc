#include "SetDialog.hh"

SetDialog::SetDialog(Gtk::Window &parent)
:vbox(Gtk::ORIENTATION_VERTICAL,5),
hbox(Gtk::ORIENTATION_HORIZONTAL,5),
btnback("BackGround")
{
    Gtk::Label label1("BackGround File Name:");
    //Ininalize Dialog
    set_title("Settings");
    set_default_size(300,150);
    set_transient_for(parent);
    add_button("OK",Gtk::RESPONSE_OK);
    add_button("Cancel",Gtk::RESPONSE_CANCEL);

    //Add Widgets
    auto pbox=get_content_area();
    vbox.set_halign(Gtk::ALIGN_CENTER);
    vbox.set_valign(Gtk::ALIGN_CENTER);
    pbox->pack_start(vbox);

    //Button Box
    hbox.pack_start(entry_back,Gtk::PACK_SHRINK);
    hbox.pack_start(btnback,Gtk::PACK_SHRINK);
    vbox.pack_start(label1,Gtk::PACK_SHRINK);
    vbox.pack_start(hbox,Gtk::PACK_SHRINK);

    //Signals
    btnback.signal_clicked().connect(sigc::mem_fun(*this,&SetDialog::btnback_clicked));
}

void SetDialog::set_config(conf_map * src_config,Gtk::Image * src_image){
    //Set Config to the Dialog
    configs1=src_config;
    img_back=src_image;
    std::string filename=(*src_config)["background"];
    entry_back.set_text(filename);
}

void SetDialog::on_response(int response_id){
    if(response_id == Gtk::RESPONSE_OK){
        Glib::ustring backname=entry_back.get_text();
        //Change Background
        if(!backname.empty()){
            auto pixbuf=Gdk::Pixbuf::create_from_file(backname);
            auto sized=pixbuf->scale_simple(640,360,Gdk::INTERP_BILINEAR);
            gtk_image_set_from_pixbuf(img_back->gobj(),sized->gobj());
            pixbuf.reset();
            sized.reset();
        }
        //Write filename to config file
        outfile.open("config",std::ios_base::out);
        if(outfile.is_open()){
           outfile<<"background="<<backname<<std::endl; 
        }
        outfile.close();
    }
    hide();
}

void SetDialog::btnback_clicked(){
    //Create a Dialog
    dialog=Gtk::FileChooserNative::create("Open a Image File",*this,
                                          Gtk::FILE_CHOOSER_ACTION_OPEN,"OK","Cancel");
    
    dialog->signal_response().connect(sigc::mem_fun(*this,&SetDialog::dialog_reponse));

    //Add a FileFilter
    auto filter_any=Gtk::FileFilter::create();
    filter_any->set_name("Any Files");
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);

    dialog->show();
}

void SetDialog::dialog_reponse(int response_id){
    if(response_id == Gtk::RESPONSE_ACCEPT){
        //Set filename to entry
        Glib::ustring filename=dialog->get_filename();
        entry_back.set_text(filename);
    }
    dialog.reset();
}
