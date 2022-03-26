#pragma once

#include <gtkmm.h>

class ColorButton : public Gtk::Button
{
public:
    ColorButton();

private:

    // Child widgets
    Gdk::RGBA rgba;
    Gtk::Image image;

    // Signal Handlers
    bool image_draw(const Cairo::RefPtr<Cairo::Context> &context);
};

class ColorRef
{
    
};