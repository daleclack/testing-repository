#include "MyImage.hh"

MyImage::MyImage(){

}

MyImage::~MyImage(){

}

bool MyImage::on_draw(const Cairo::RefPtr<Cairo::Context> &cr){
    if(!image){
        return false;
    }

    int width = image->get_width();
    int height = image->get_height();

    //Set the default size for drawing area
    set_size_request(width,height);

    // Draw the image in the middle of the drawing area, or (if the image is
    // larger than the drawing area) draw the middle part of the image.
    Gdk::Cairo::set_source_pixbuf(cr, image,
        (width - image->get_width())/2, (height - image->get_height())/2);
    
    cr->paint();

    return true;
}

void MyImage::set_pixbuf(const Glib::RefPtr<Gdk::Pixbuf> &pixbuf)
{
    if(image){
        image.reset();
    }
    
    image = pixbuf;

    //ReDraw the draw area
    queue_draw();
}
