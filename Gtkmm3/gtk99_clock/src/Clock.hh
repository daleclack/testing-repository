#pragma once

#include <gtkmm/drawingarea.h>

class Clock : public Gtk::DrawingArea{
public:
    Clock();
protected:
    //Default Signals
    bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

    bool on_timeout();

    //Radius for the circle
    double m_radius;
    double m_line_width;
};
