#include "MyArea.hh"

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    double x0 = 0.1, y0 = 0.5, // start point
        x1 = 0.4, y1 = 0.9,    // control point #1
        x2 = 0.6, y2 = 0.1,    // control point #2
        x3 = 0.9, y3 = 0.5;    // end point

    // scale to unit square (0 to 1 width and height)
    cr->scale(width, height);

    cr->set_line_width(0.05);
    // draw curve
    cr->move_to(x0, y0);
    cr->curve_to(x1, y1, x2, y2, x3, y3);
    cr->stroke();
    // show control points
    cr->set_source_rgba(1, 0.2, 0.2, 0.6);
    cr->move_to(x0, y0);
    cr->line_to(x1, y1);
    cr->move_to(x2, y2);
    cr->line_to(x3, y3);
    cr->stroke();

    return true;
}
