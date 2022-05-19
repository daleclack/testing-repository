#pragma once

#include <gtkmm.h>

// 4 Draw modes: default(free draw), circle, line, rectangle
enum class DrawMode{
    Default,
    Circle,
    Line,
    Rectangle
};

// Flage for process of drawing
enum class DrawProcess{
    Begin,      // The beginning of draw
    Update,     // The Process(Position update)
    End         // The end of draw
};

class Drawing : public Gtk::Window
{
    // Drawing Mode
    DrawMode drawing_mode;

    // Child Widgets
    Gtk::DrawingArea draw_area;
    Gtk::ColorButton color_btn;
    Gtk::Label main_label, size_label, pos_label, pos_label1;
    Gtk::Box left_box, main_box, btn_box;
    Gtk::Button btn_clear, btn_exit;
    Gtk::RadioButton btn_free, btn_line, btn_circle, btn_rectangle;
    Gtk::Scale scale;

    // Color Setting
    Gdk::RGBA m_color;
    Cairo::RefPtr<Cairo::ImageSurface> surface;

    // Draw Brush Settings
    double brush_size;
    double rel_x, rel_y;
    bool begin = true;

    // Gesture to draw
    Glib::RefPtr<Gtk::GestureDrag> drag;
    Glib::RefPtr<Gtk::GestureMultiPress> press;
    Glib::RefPtr<Gtk::Adjustment> size_adj;
    double start_x, start_y;

    // Signal Handlers
    bool draw_event(const Cairo::RefPtr<Cairo::Context> &context);

    void draw_brush(double x, double y, DrawProcess process = DrawProcess::Update);

    void button_press(int n_press, double x, double y);

    void drag_begin(double x, double y);

    void drag_progress(double x, double y);

    void drag_end(double x, double y);

    void color_set();

    void btnfree_clicked();

    void btnline_clicked();

    void btncircle_clicked();

    void btnrectangle_clicked();

    void btnclear_clicked();

public:
    Drawing();
};
