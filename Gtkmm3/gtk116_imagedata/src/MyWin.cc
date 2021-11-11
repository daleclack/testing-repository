#include "MyWin.hh"
#include <iostream>
#include "winpe.xpm"

MyWin::MyWin(){
    set_icon_name("org.gtk.daleclack");
    background.set_size_request(640,360);
    
    //Create a pixbuf
    pixbuf = Gdk::Pixbuf::create_from_xpm_data(winpe);
    sized = pixbuf->scale_simple(640,360,Gdk::INTERP_BILINEAR);

    //Set image
    gtk_image_set_from_pixbuf(background.gobj(),sized->gobj());
    get_pixel_color(320,180);
    add(background);
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