#include "MyWin.hh"
#include <iostream>
#include "image_types.hh"
#include "winpe.xpm"

MyWin::MyWin()
:btn_back("Background")
{
    set_icon_name("org.gtk.daleclack");
    background.set_size_request(640,360);
    
    //Create a pixbuf
    pixbuf = Gdk::Pixbuf::create_from_xpm_data(winpe);
    sized = pixbuf->scale_simple(640,360,Gdk::INTERP_BILINEAR);

    //Add Button
    btn_back.set_halign(Gtk::ALIGN_CENTER);
    btn_back.set_valign(Gtk::ALIGN_CENTER);
    m_overlay.add_overlay(btn_back);
    btn_back.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnback_clicked));

    //Set image
    gtk_image_set_from_pixbuf(background.gobj(),sized->gobj());
    get_pixel_color(320,180);
    m_overlay.add(background);
    add(m_overlay);
    show_all_children();
    pixbuf.reset();
}

void MyWin::get_pixel_color(int x,int y){
    //Get Image data
    int red=0,green=0,blue=0,alpha=0;
    int n_channels = sized->get_n_channels();
    int rowstride = sized->get_rowstride();         //Rows

    //Get Pixel data
    guint8 * pixels = sized->get_pixels();

    //Get Color at specified location
    for(int i = x-2; i <= x+2; i++){
        for(int j = y-2; j <= y+2; j++){
            guchar * p = pixels + y * rowstride + x * n_channels;
            red += p[0];
            green += p[1];
            blue += p[2];
            if(sized->get_has_alpha()){
                alpha += p[4];
            }else{
                alpha += 255;
            }
        }       
    }
    red/=25;blue/=25;green/=25;alpha/=25;

    //OutPut the color rgba set
    if(pixbuf->get_has_alpha()){
        std::cout<<red<<" "<<green<<" "<<blue<<" "<<alpha<<std::endl;
    }else{
        std::cout<<red<<" "<<green<<" "<<blue<<" "<<alpha<<std::endl;
    }
}

void MyWin::btnback_clicked(){
    //Initalize Dialog
    dialog = Gtk::FileChooserNative::create("Open a image file",*this,Gtk::FILE_CHOOSER_ACTION_OPEN,
                                            "OK","Cancel");
    
    //Add filter for Image files
    auto filter_image = Gtk::FileFilter::create();
    filter_image->set_name("Image Files");
    if(mime_type_supported()){
        //For systems that supports mime type, add a mime type
        filter_image->add_mime_type("image/*");
    }else{
        //For Systems that not support mime type, use a supported globs
        for(int i=0; supported_globs!=NULL && supported_globs[i]!=NULL; i++){
            const char * glob = supported_globs[i];
            filter_image->add_pattern(glob);
        }
    }
    dialog->add_filter(filter_image);

    //Filter for any files
    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any Files");
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);

    //Link the "reponse" signal of dialog and show dialog
    dialog->signal_response().connect(sigc::mem_fun(*this,&MyWin::set_background));
    dialog->show();
}

void MyWin::set_background(int response_id){
    if(response_id == Gtk::RESPONSE_ACCEPT){
        Glib::ustring filename = dialog->get_filename();
        pixbuf = Gdk::Pixbuf::create_from_file(filename);
        //Release memory of pixbuf "sized"
        sized.reset();
        sized = pixbuf->scale_simple(640,360,Gdk::INTERP_BILINEAR);
        gtk_image_set_from_pixbuf(background.gobj(),sized->gobj());
        get_pixel_color(320,180);
    }
    dialog.reset();
}
