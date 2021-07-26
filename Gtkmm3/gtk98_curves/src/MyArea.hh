#pragma once

#include <gtkmm/drawingarea.h>

class MyArea : public Gtk::DrawingArea{
protected:
    //Override default signal handler:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};
