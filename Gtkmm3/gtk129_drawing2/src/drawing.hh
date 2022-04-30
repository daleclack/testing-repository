#pragma once

#include <gtkmm.h>

enum class DrawMode{
    Default,
    Line
};

class Drawing : public Gtk::Window
{
    // Drawing Mode
    DrawMode drawing_mode;

    // Child Widgets
    Gtk::DrawingArea draw_area;
    Gtk::ColorButton color_btn;
    Gtk::Label main_label, size_label;
    Gtk::Box main_box, btn_box;
    Gtk::Button btn_line, btn_clear, btn_exit;
    Gtk::Scale scale;

    // Color Setting
    Gdk::RGBA m_color;
    Cairo::RefPtr<Cairo::ImageSurface> surface;

    // Gesture to draw
    Glib::RefPtr<Gtk::GestureDrag> drag;
    Glib::RefPtr<Gtk::Adjustment> size_adj;
    double start_x, start_y;

    // Signal Handlers
    bool draw_event(const Cairo::RefPtr<Cairo::Context> &context);

    void draw_brush(double x, double y, bool begin = false);

    void button_press();

    void drag_begin(double x, double y);

    void drag_progress(double x, double y);

    void color_set();

public:
    Drawing();
};
