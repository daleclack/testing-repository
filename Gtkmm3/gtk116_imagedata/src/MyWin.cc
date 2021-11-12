#include "MyWin.hh"
#include <cstdio>
#include "image_types.hh"
#include "winpe.xpm"

MyWin::MyWin()
:btn_back("Open Image"),
hbox(Gtk::ORIENTATION_HORIZONTAL,5),
btnbox(Gtk::ORIENTATION_VERTICAL,5)
{
    set_icon_name("org.gtk.daleclack");
    background.set_size_request(640,480);
    
    //Create a pixbuf
    pixbuf = Gdk::Pixbuf::create_from_xpm_data(winpe);
    sized = pixbuf->scale_simple(640,480,Gdk::INTERP_BILINEAR);

    //Add Button
    btn_back.set_halign(Gtk::ALIGN_CENTER);
    btn_back.set_valign(Gtk::ALIGN_CENTER);
    btn_back.set_relief(Gtk::RELIEF_NONE);
    btn_back.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnback_clicked));

    //Add Gesture
    gesture = Gtk::GestureMultiPress::create(draw_area);
    gesture->set_button(1);
    gesture->signal_pressed().connect(sigc::mem_fun(*this,&MyWin::gesture_pressed));
    draw_area.set_hexpand();
    draw_area.set_vexpand();
    m_overlay.add_overlay(draw_area);

    //Set image
    gtk_image_set_from_pixbuf(background.gobj(),sized->gobj());
    //get_pixel_color(320,180);

    //Add Color and Image Button
    color_btn.set_use_alpha();
    btnbox.pack_start(label_pos,Gtk::PACK_SHRINK);
    btnbox.pack_start(label_rgba,Gtk::PACK_SHRINK);
    btnbox.pack_start(color_btn,Gtk::PACK_SHRINK);
    btnbox.pack_start(btn_back,Gtk::PACK_SHRINK);
    btnbox.set_valign(Gtk::ALIGN_CENTER);

    //Add Widgets and show all
    m_overlay.add(background);
    hbox.pack_start(m_overlay);
    hbox.pack_start(btnbox,Gtk::PACK_SHRINK);
    add(hbox);
    show_all_children();
    pixbuf.reset();
}

void MyWin::get_pixel_color(int x,int y){
    //Get Image data
    Gdk::RGBA color_set;
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

    //Set Color to rgba
    color_set.set_red(red/25.0/255.0);
    color_set.set_blue(blue/25.0/255.0);
    color_set.set_green(green/25.0/255.0);
    color_set.set_alpha(alpha/25.0/255.0);

    //Get Color set as a string
    label_rgba.set_label(color_set.to_string());

    //OutPut the color rgba set
    color_btn.set_rgba(color_set);
}

void MyWin::gesture_pressed(int n_press,double x,double y){
    char pos[57];
    sprintf(pos,"(%.2f,%.2f)",x,y);
    label_pos.set_label(pos);
    get_pixel_color((int)x, (int)y);
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
        sized = pixbuf->scale_simple(640,480,Gdk::INTERP_BILINEAR);
        gtk_image_set_from_pixbuf(background.gobj(),sized->gobj());
        get_pixel_color(320,180);
    }
    dialog.reset();
}
