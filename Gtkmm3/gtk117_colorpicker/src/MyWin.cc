#include "MyWin.hh"
#include <cstdio>
#include <iostream>
#include "image_types.hh"
#include "winpe.xpm"

MyWin::MyWin()
:btn_back("Open Image"),
hbox(Gtk::ORIENTATION_HORIZONTAL,5),
btnbox(Gtk::ORIENTATION_VERTICAL,5),
frame_pos("Position"),
frame_css_rgba("rgba() for css3"),
frame_rgba_str("RGBA Code"),
label_pos("(640,480)"),
label_css_rgba("rgba(255,255,255,255)"),
label_test("Color Settings And Position info"),
label_color_str("#00000000"),
btn_css_code("Copy Css3 Code"),
btn_color_str("Copy RGB(A) String")
{
    set_title("Color Picker");
    set_icon_name("org.gtk.daleclack");
    background.set_size_request(640,480);
    
    //Create a pixbuf
    pixbuf = Gdk::Pixbuf::create_from_xpm_data(winpe);
    sized = pixbuf->scale_simple(640,480,Gdk::INTERP_BILINEAR);

    //Add Button
    btn_back.set_halign(Gtk::ALIGN_CENTER);
    btn_back.set_valign(Gtk::ALIGN_CENTER);
    btn_back.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnback_clicked));

    btn_css_code.set_halign(Gtk::ALIGN_CENTER);
    btn_css_code.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btncss_clicked));
    btn_color_str.set_halign(Gtk::ALIGN_CENTER);
    btn_color_str.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btncolor_clicked));

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
    color_btn.set_halign(Gtk::ALIGN_CENTER);
    btnbox.pack_start(label_test,Gtk::PACK_SHRINK);

    frame_pos.add(label_pos);
    btnbox.pack_start(frame_pos,Gtk::PACK_SHRINK);

    frame_css_rgba.add(label_css_rgba);
    btnbox.pack_start(frame_css_rgba,Gtk::PACK_SHRINK);

    frame_rgba_str.add(label_color_str);
    btnbox.pack_start(frame_rgba_str,Gtk::PACK_SHRINK);

    btnbox.pack_start(color_btn);
    btnbox.pack_start(btn_back);
    btnbox.pack_start(btn_css_code);
    btnbox.pack_start(btn_color_str);
    btnbox.set_valign(Gtk::ALIGN_CENTER);

    //Add Widgets and show all
    m_overlay.add(background);
    hbox.pack_start(m_overlay);
    hbox.pack_start(btnbox);
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
    Glib::ustring color_str;

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
    red/=25;blue/=25;green/=25;alpha/=25;
    color_set.set_red(red/255.0);
    color_set.set_blue(blue/255.0);
    color_set.set_green(green/255.0);
    color_set.set_alpha(alpha/255.0);

    //Get Color set as a string
    label_css_rgba.set_label(color_set.to_string());

    //OutPut the color rgba set
    color_btn.set_rgba(color_set);

    //OutPut color Set as a Color Code
    //If the image has a alpha value, use RGBA Code, else use RGB Code
    if(sized->get_has_alpha()){
        color_str = Glib::ustring(g_strdup_printf("#%02X%02X%02X%02X",red,blue,green,alpha));
    }else{
        color_str = Glib::ustring(g_strdup_printf("#%02X%02X%02X",red,blue,green));
    }
    label_color_str.set_label(color_str);
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

void MyWin::btncss_clicked(){
    //Copy contents of label for css3 code
    auto clipboard = Gtk::Clipboard::get();
    Glib::ustring str = label_css_rgba.get_label();
    clipboard->set_text(str);
}

void MyWin::btncolor_clicked(){
    //Copy contents of label for rgba code
    auto clipboard = Gtk::Clipboard::get();
    Glib::ustring str = label_color_str.get_label();
    clipboard->set_text(str);
}
