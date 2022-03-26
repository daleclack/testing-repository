#pragma once

#include <gtkmm.h>

class ColorButton : public Gtk::Button
{
public:
    ColorButton();

private:
    Gdk::RGBA rgba;
    Gtk::Image image;
    bool image_draw(const Cairo::RefPtr<Cairo::Context> &context);
};

class ColorRef
{
};