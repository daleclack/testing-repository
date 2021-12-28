#include "MyImage.hh"

MyImage::MyImage()
    : scale_radio(1.0)
{
}

MyImage::~MyImage()
{
}

bool MyImage::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    if (!image)
    {
        return false;
    }

    // Set the default size for drawing area
    set_size_request(surface->get_width() * scale_radio,
                     surface->get_height() * scale_radio);

    cr->scale(scale_radio, scale_radio);
    cr->set_source(surface, 0, 0);

    cr->paint();

    return true;
}

void MyImage::scale_draw(double scale)
{
    // Set the scale radio and scale
    if (scale <= 0)
    {
        scale_radio = 0.1;
        return;
    }
    if (scale > 10.0)
    {
        scale_radio = 10.0;
        return;
    }
    scale_radio = scale;
    queue_draw();
}

void MyImage::set_pixbuf(const Glib::RefPtr<Gdk::Pixbuf> &pixbuf)
{
    if (image)
    {
        image.reset();
    }

    image = pixbuf;

    if (!surface)
    {
        // Create a surface
        surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32,
                                              image->get_width(), image->get_height());
    }
    else
    {
    }

    // Get Image Size
    int width = image->get_width();
    int height = image->get_height();
    // Draw the image in the middle of the surface, or (if the image is
    // larger than the drawing area) draw the middle part of the image.
    auto cr = Cairo::Context::create(surface);
    Gdk::Cairo::set_source_pixbuf(cr, image,
                                  (width - image->get_width()) / 2, (height - image->get_height()) / 2);
    cr->paint();

    // ReDraw the draw area
    queue_draw();
}
