#include "winpe.xpm"
#include "BackGround.hh"
#include "image_types.hh"

BackGround::BackGround(Gtk::Window &parent,Gtk::Image *back)
:btn_default("Use Default Background"),
btn_set("Set Background From a File")
{
    //Initalize Dialog
    set_default_size(300,100);
    set_title("Change Background");
    set_transient_for(parent);
    add_button("Close",Gtk::RESPONSE_CLOSE);
    background=back;

    Gtk::Box * vbox=get_content_area();
    vbox->pack_start(btn_default,Gtk::PACK_SHRINK);
    btn_default.signal_clicked().connect(sigc::mem_fun(*this,&BackGround::default_background));
    vbox->pack_start(btn_set,Gtk::PACK_SHRINK);
    btn_set.signal_clicked().connect(sigc::mem_fun(*this,&BackGround::btnset_clicked));
}

void BackGround::btnset_clicked(){
    Gtk::FileChooserDialog dialog1("Choose an image file",
                                  Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog1.set_transient_for(*this);

    //Add reponse buttons
    dialog1.add_button("_Cancel",Gtk::RESPONSE_CANCEL);
    dialog1.add_button("_OK",Gtk::RESPONSE_OK);
    
    //Add filters
    auto filter_image=Gtk::FileFilter::create();
    filter_image->set_name("Image Files");

    //Windows doesn't support mime type
    if(mime_type_supported()){
        filter_image->add_mime_type("image/*");
    }else{
        for(int i=0;supported_globs!=NULL && supported_globs[i]!=NULL ;i++){
            filter_image->add_pattern(supported_globs[i]);
        }
    }

    dialog1.add_filter(filter_image);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog1.add_filter(filter_any);

    //Show the dialog and wait for a user response:
    int result = dialog1.run();

    if(result==Gtk::RESPONSE_OK){
        //Get the image file and set the image from the file
        std::string filename;
        filename=dialog1.get_filename();
        Glib::RefPtr<Gdk::Pixbuf> pixbuf=Gdk::Pixbuf::create_from_file(filename);
        Glib::RefPtr<Gdk::Pixbuf> sized=pixbuf->scale_simple(640,360,Gdk::INTERP_BILINEAR);
        gtk_image_set_from_pixbuf(background->gobj(),sized->gobj());
        //Free the memory
        pixbuf.reset();
        sized.reset();
    }
    filter_image.reset();
    filter_any.reset();
}

void BackGround::default_background(){
    //Background
    Glib::RefPtr<Gdk::Pixbuf> pixbuf=Gdk::Pixbuf::create_from_xpm_data(winpe);
    Glib::RefPtr<Gdk::Pixbuf> sized=pixbuf->scale_simple(640,360,Gdk::INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(background->gobj(),sized->gobj());
    //Release Memory
    pixbuf.reset();
    sized.reset();
}

void BackGround::on_response(int response_id){
    hide();
}