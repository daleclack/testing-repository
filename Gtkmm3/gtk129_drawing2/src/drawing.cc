#include "drawing.hh"
#include <iostream>

Drawing::Drawing()
    : main_label("Select a color"),
      size_label("Pen Size"),
      main_box(Gtk::ORIENTATION_HORIZONTAL, 5),
      btn_box(Gtk::ORIENTATION_VERTICAL, 5),
      btn_line("Line to"),
      btn_clear("Clear Board"),
      btn_exit("Exit")
{
    // Ininalize window
    set_icon_name("org.gtk.daleclack");
    set_title("Drawing");
    set_default_size(640, 480);

    // Color set panel
    size_adj = Gtk::Adjustment::create(3.0, 1.0, 20.0);
    scale.set_adjustment(size_adj);
    scale.set_value_pos(Gtk::POS_BOTTOM);
    btn_box.pack_start(main_label, Gtk::PACK_SHRINK);
    btn_box.pack_start(color_btn, Gtk::PACK_SHRINK);
    btn_box.pack_start(size_label, Gtk::PACK_SHRINK);
    btn_box.pack_start(scale, Gtk::PACK_SHRINK);
    btn_box.pack_start(btn_clear, Gtk::PACK_SHRINK);
    btn_box.pack_start(btn_exit, Gtk::PACK_SHRINK);
    btn_box.set_halign(Gtk::ALIGN_CENTER);
    btn_box.set_valign(Gtk::ALIGN_CENTER);

    // Add Gesture
    btn_clear.signal_clicked().connect(sigc::mem_fun(*this, &Drawing::button_press));
    btn_exit.signal_clicked().connect(sigc::mem_fun(*this, &Drawing::hide));

    drag = Gtk::GestureDrag::create(draw_area);
    drag->set_button(GDK_BUTTON_PRIMARY);
    drag->signal_drag_begin().connect(sigc::mem_fun(*this, &Drawing::drag_begin));
    drag->signal_drag_update().connect(sigc::mem_fun(*this, &Drawing::drag_progress));
    drag->signal_drag_end().connect(sigc::mem_fun(*this, &Drawing::drag_progress));

    // Create a Surface
    surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 600, 480);

    // Set Default Color
    m_color.set_blue(0);
    m_color.set_green(0);
    m_color.set_red(0);
    m_color.set_alpha(1);
    color_btn.set_rgba(m_color);
    color_btn.signal_color_set().connect(sigc::mem_fun(*this, &Drawing::color_set));

    // Initalial draw
    auto cr = Cairo::Context::create(surface);
    cr->set_source_rgb(1, 1, 1);
    cr->paint();
    cr.clear();
    draw_area.queue_draw();

    // Set Draw mode to default
    drawing_mode = DrawMode::Default;

    // Initalize main widget
    draw_area.set_size_request(600, 480);
    draw_area.signal_draw().connect(sigc::mem_fun(*this, &Drawing::draw_event));
    main_box.pack_start(draw_area);
    main_box.pack_start(btn_box, Gtk::PACK_SHRINK);
    main_box.set_border_width(10);
    add(main_box);
    show_all_children();
}

// Signal Handlers
bool Drawing::draw_event(const Cairo::RefPtr<Cairo::Context> &context)
{
    // Show context
    context->set_source(surface, 0, 0);
    context->paint();
    return true;
}

void Drawing::draw_brush(double x, double y, bool begin)
{
    double size = scale.get_value();
    auto cr = Cairo::Context::create(surface);
    static int count = 0;
    static double x1, y1;

    switch (drawing_mode)
    {
    case DrawMode::Default:
        // Create Draw Brush with specificed size
        cr->set_line_width(G_PI * size);
        if (begin)
        {
            x1 = x;
            y1 = y;
        }
        else
        {
            cr->move_to(x1, y1);
            cr->line_to(x, y);
            x1 = x;
            y1 = y;
        }

        // Set Color
        cr->set_source_rgba(m_color.get_red(), m_color.get_green(),
                            m_color.get_blue(), m_color.get_alpha());

        // Fill Color and Delete the brush
        cr->stroke();
        cr.clear();
        break;
    case DrawMode::Line:
        break;
    }
    draw_area.queue_draw();
}

void Drawing::button_press()
{
    if (surface)
    {
        // Clear the content in draw area
        auto cr = Cairo::Context::create(surface);
        cr->set_source_rgb(1, 1, 1);
        cr->paint();
        cr.clear();
        draw_area.queue_draw();
    }
}

void Drawing::drag_begin(double x, double y)
{
    // The Begin
    start_x = x;
    start_y = y;
    draw_brush(x, y, true);
}

void Drawing::drag_progress(double x, double y)
{
    // Progress and end
    draw_brush(x + start_x, y + start_y);
}

void Drawing::color_set()
{
    m_color = color_btn.get_rgba();
}
