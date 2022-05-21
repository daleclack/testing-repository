#include "drawing.hh"
#include <algorithm>
#include <iostream>

Drawing::Drawing()
    : fill_check("Enable Fill Color"),
      main_label("Select a color"),
      size_label("Pen Size"),
      left_box(Gtk::ORIENTATION_VERTICAL, 5),
      main_box(Gtk::ORIENTATION_HORIZONTAL, 5),
      btn_box(Gtk::ORIENTATION_VERTICAL, 5),
      btn_clear("Clear Board"),
      btn_save("Save to png"),
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
    btn_free.signal_clicked().connect(sigc::mem_fun(*this, &Drawing::btnfree_clicked));
    btn_circle.set_image_from_icon_name("circle");
    btn_circle.set_always_show_image();
    btn_circle.signal_clicked().connect(sigc::mem_fun(*this, &Drawing::btncircle_clicked));
    btn_line.set_image_from_icon_name("line");
    btn_line.set_always_show_image();
    btn_line.signal_clicked().connect(sigc::mem_fun(*this, &Drawing::btnline_clicked));
    btn_rectangle.set_image_from_icon_name("rectangle");
    btn_rectangle.set_always_show_image();
    btn_rectangle.signal_clicked().connect(sigc::mem_fun(*this, &Drawing::btnrectangle_clicked));

    // Left Panel
    left_box.pack_start(btn_free, Gtk::PACK_SHRINK);
    left_box.pack_start(btn_circle, Gtk::PACK_SHRINK);
    left_box.pack_start(btn_line, Gtk::PACK_SHRINK);
    left_box.pack_start(btn_rectangle, Gtk::PACK_SHRINK);
    left_box.set_valign(Gtk::ALIGN_START);

    // Color set panel
    size_adj = Gtk::Adjustment::create(3.0, 1.0, 20.0);
    scale.set_adjustment(size_adj);
    scale.set_value_pos(Gtk::POS_BOTTOM);
    btn_box.pack_start(fill_check, Gtk::PACK_SHRINK);
    btn_box.pack_start(fill_btn, Gtk::PACK_SHRINK);
    btn_box.pack_start(main_label, Gtk::PACK_SHRINK);
    btn_box.pack_start(color_btn, Gtk::PACK_SHRINK);
    btn_box.pack_start(size_label, Gtk::PACK_SHRINK);
    btn_box.pack_start(scale, Gtk::PACK_SHRINK);
    btn_box.pack_start(btn_save, Gtk::PACK_SHRINK);
    btn_box.pack_start(btn_clear, Gtk::PACK_SHRINK);
    btn_box.pack_start(btn_exit, Gtk::PACK_SHRINK);
    btn_box.set_halign(Gtk::ALIGN_CENTER);
    btn_box.set_valign(Gtk::ALIGN_CENTER);

    // Add Gesture
    btn_clear.signal_clicked().connect(sigc::mem_fun(*this, &Drawing::btnclear_clicked));
    btn_save.signal_clicked().connect(sigc::mem_fun(*this, &Drawing::btnsave_clicked));
    btn_exit.signal_clicked().connect(sigc::mem_fun(*this, &Drawing::hide));

    drag = Gtk::GestureDrag::create(draw_area);
    drag->set_button(GDK_BUTTON_PRIMARY);
    drag->signal_drag_begin().connect(sigc::mem_fun(*this, &Drawing::drag_begin));
    drag->signal_drag_update().connect(sigc::mem_fun(*this, &Drawing::drag_progress));
    drag->signal_drag_end().connect(sigc::mem_fun(*this, &Drawing::drag_end));

    press = Gtk::GestureMultiPress::create(draw_area);
    press->set_button();
    press->signal_pressed().connect(sigc::mem_fun(*this, &Drawing::button_press));

    // Create a Surface
    surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 600, 480);

    // Set Default Color
    m_color.set_blue(0);
    m_color.set_green(0);
    m_color.set_red(0);
    m_color.set_alpha(1);
    color_btn.set_rgba(m_color);
    color_btn.signal_color_set().connect(sigc::mem_fun(*this, &Drawing::color_set));
    fill_color = m_color;
    fill_btn.set_rgba(fill_color);
    fill_btn.signal_color_set().connect(sigc::mem_fun(*this, &Drawing::color_set));

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

void Drawing::btnsave_clicked()
{
    // Create a dialog
    dialog = Gtk::FileChooserNative::create("Save to png file", *this,
                                            Gtk::FILE_CHOOSER_ACTION_SAVE, "OK", "Cancel");

    // Link Signal
    dialog->signal_response().connect(sigc::mem_fun(*this, &Drawing::dialog_response));

    // Create Filters

    auto filter_png = Gtk::FileFilter::create();
    filter_png->set_name("Png files");
    filter_png->add_pattern("*.png");
    dialog->add_filter(filter_png);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any Files");
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);

    dialog->show();
}

void Drawing::dialog_response(int response_id)
{
    // Save cairo surface to png file
    if (response_id == Gtk::RESPONSE_ACCEPT)
    {
        // Get file name
        std::string filename;
        auto file = dialog->get_file();
        filename = file->get_path();

        // Auto complete the extension of the image file
        size_t length = filename.length();
        std::string extension = filename.substr(length-3,length-1);
        std::transform(extension.begin(),extension.end(),extension.begin(),::tolower);
        if(extension != "png"){
            filename += ".png";
        }

        // Write surface data to the file
        surface->write_to_png(filename);
    }
    dialog.reset();
}

void Drawing::btnfree_clicked()
{
    // Mode1: Free Drawing
    drawing_mode = DrawMode::Default;
}

void Drawing::btnline_clicked()
{
    // Mode2: Draw line, click for start point and end point
    drawing_mode = DrawMode::Line;
}

void Drawing::btncircle_clicked()
{
    // Mode3: Draw circle, click for radius
    drawing_mode = DrawMode::Circle;
}

void Drawing::btnrectangle_clicked()
{
    // Mode4: Draw a rectangle
    drawing_mode = DrawMode::Rectangle;
}

void Drawing::btnclear_clicked()
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

// Signal Handlers
bool Drawing::draw_event(const Cairo::RefPtr<Cairo::Context> &context)
{
    // Show context
    context->set_source(surface, 0, 0);
    context->paint();
    return true;
}

void Drawing::draw_brush(double x, double y, DrawProcess process)
{
    brush_size = scale.get_value();
    auto cr = Cairo::Context::create(surface);

    // Create Draw Brush with specificed size
    cr->set_line_width(brush_size * 2);

    switch (drawing_mode)
    {
    case DrawMode::Default:
        // Use Line for main drawing
        if (process == DrawProcess::Begin)
        {
            rel_x = x;
            rel_y = y;
        }
        else
        {
            cr->move_to(rel_x - 0.1, rel_y - 0.1);
            cr->line_to(x, y);
            rel_x = x;
            rel_y = y;
        }

        // Set Color
        cr->set_source_rgba(m_color.get_red(), m_color.get_green(),
                            m_color.get_blue(), m_color.get_alpha());

        // Fill Color and Delete the brush
        cr->stroke();
        cr.clear();
        break;
    case DrawMode::Line:
        cr->move_to(rel_x, rel_y);
        cr->line_to(x, y);

        // Set Color
        cr->set_source_rgba(m_color.get_red(), m_color.get_green(),
                            m_color.get_blue(), m_color.get_alpha());

        // Fill Color and Delete the brush
        cr->stroke();
        cr.clear();
        break;
    case DrawMode::Circle:
        // Fill Color and Delete the brush
        if (fill_check.get_active())
        {
            cr->arc(rel_x, rel_y, sqrt((x - rel_x) * (x - rel_x) + (y - rel_y) * (y - rel_y)), 0.0, 2 * G_PI);
            // Fill Color
            draw_fill_color(cr);
        }

        cr->arc(rel_x, rel_y, sqrt((x - rel_x) * (x - rel_x) + (y - rel_y) * (y - rel_y)), 0.0, 2 * G_PI);

        cr->set_source_rgba(m_color.get_red(), m_color.get_green(),
                            m_color.get_blue(), m_color.get_alpha());
        cr->stroke();
        cr.clear();
        break;
    case DrawMode::Rectangle:
        // Fill Color and Delete the brush
        if (fill_check.get_active())
        {
            // Fill Color
            cr->rectangle(rel_x, rel_y, abs(x - rel_x), abs(y - rel_y));
            draw_fill_color(cr);
        }
        cr->rectangle(rel_x, rel_y, abs(x - rel_x), abs(y - rel_y));

        cr->set_source_rgba(m_color.get_red(), m_color.get_green(),
                            m_color.get_blue(), m_color.get_alpha());
        cr->stroke();
        cr.clear();
        break;
    }
    draw_area.queue_draw();
}

void Drawing::draw_fill_color(const Cairo::RefPtr<Cairo::Context> &cr)
{
    cr->set_source_rgba(fill_color.get_red(), fill_color.get_green(),
                        fill_color.get_blue(), fill_color.get_alpha());
    cr->fill();
}

void Drawing::button_press(int n_press, double x, double y)
{
    auto button = press->get_current_button();
    // std::cout<<button<<std::endl;
    switch (button)
    {
    case 1:
        if (drawing_mode != DrawMode::Default)
        {
            if (begin)
            {
                begin = !begin;
                rel_x = x;
                rel_y = y;
            }
            else
            {
                begin = !begin;
                draw_brush(x, y, DrawProcess::End);
            }
        }
        break;
    case 3:
        btnclear_clicked();
        break;
    }
}

void Drawing::drag_begin(double x, double y)
{
    start_x = x;
    start_y = y;
    draw_brush(x, y, DrawProcess::Begin);
}

void Drawing::drag_progress(double x, double y)
{
    // Progress and end
    draw_brush(x + start_x, y + start_y, DrawProcess::Update);
}

void Drawing::drag_end(double x, double y)
{
    // Progress and end
    draw_brush(x + start_x, y + start_y, DrawProcess::End);
}

void Drawing::color_set()
{
    m_color = color_btn.get_rgba();
    fill_color = fill_btn.get_rgba();
}
