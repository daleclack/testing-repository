#pragma once

#include <gtkmm.h>
#include <glibmm/i18n.h>

class ColorPanel : public Gtk::Box
{
public:
    ColorPanel(BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade);
    static ColorPanel * create();

private:
    // Child widgets
    Gtk::Scale * scale_alpha, * scale_red, * scale_green, * scale_blue;
    Gtk::DrawingArea draw_area;
    Gtk::Frame color_frame;
    Gtk::Button * btncopy;
    Gtk::Box * display_box;
    Gtk::Label * color_label;

    Glib::ustring color_str;

    // Builer
    Glib::RefPtr<Gtk::Builder> ref_builder;

    // Signal Handlers
    void scale_value_changed();
    bool drawarea_draw(const Cairo::RefPtr<Cairo::Context> &context);
    void btncopy_clicked();
};