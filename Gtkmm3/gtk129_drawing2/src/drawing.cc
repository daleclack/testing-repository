#include "drawing.hh"
#include <iostream>

Drawing::Drawing()
    : main_label("Select a color"),
      size_label("Pen Size"),
      left_box(Gtk::ORIENTATION_VERTICAL,5),
      main_box(Gtk::ORIENTATION_HORIZONTAL, 5),
      btn_box(Gtk::ORIENTATION_VERTICAL, 5),
      btn_clear("Clear Board"),
      btn_exit("Exit")
{
    // Ininalize window
    set_icon_name("org.gtk.daleclack");
    set_title("Drawing");
    set_default_size(640, 480);

    // Set the buttons grouped and set normal draw mode
    auto group = btn_free.get_group();
    btn_free.set_mode(false);
    btn_circle.set_group(group);
    btn_circle.set_mode(false);
    btn_line.set_group(group);
    btn_line.set_mode(false);
    btn_rectangle.set_group(group);
    btn_rectangle.set_mode(false);

    // Add images to the button
    btn_free.set_image_from_icon_name("freehand");
    btn_free.set_always_show_image();
    btn_circle.set_image_from_icon_name("circle");
    btn_circle.set_always_show_image();
    btn_line.set_image_from_icon_name("line");
    btn_line.set_always_show_image();
    btn_rectangle.set_image_from_icon_name("rectangle");
    btn_rectangle.set_always_show_image();

    //Left Panel
    left_box.pack_start(btn_free,Gtk::PACK_SHRINK);
    left_box.pack_start(btn_circle,Gtk::PACK_SHRINK);
    left_box.pack_start(btn_line,Gtk::PACK_SHRINK);
    left_box.pack_start(btn_rectangle,Gtk::PACK_SHRINK);
    left_box.set_valign(Gtk::ALIGN_START);

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
    main_box.pack_start(left_box);
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
        cr->set_line_width(size * 2);

        // Use Line for main drawing
        if (begin)
        {
            x1 = x;
            y1 = y;
        }
        else
        {
            cr->move_to(x1-0.1, y1-0.1);
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
