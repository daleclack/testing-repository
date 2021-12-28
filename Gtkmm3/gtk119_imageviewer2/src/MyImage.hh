#pragma once

#include <gtkmm.h>

class MyImage : public Gtk::DrawingArea
{
public:
    MyImage();
    virtual ~MyImage();
    // Set a Pixbuf to draw
    void set_pixbuf(const Glib::RefPtr<Gdk::Pixbuf> &pixbuf);
    // Scale the image
    void scale_draw(double scale);

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

private:
    double scale_radio;
    Cairo::RefPtr<Cairo::ImageSurface> surface;
    Glib::RefPtr<Gdk::Pixbuf> image;
};
