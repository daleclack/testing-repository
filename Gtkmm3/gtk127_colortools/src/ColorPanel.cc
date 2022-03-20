#include "ColorPanel.hh"

ColorPanel::ColorPanel(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade)
    : Gtk::Box(cobject),
      ref_builder(ref_Glade),
      color_frame(_("Color:"))
{
    // Get Widgets
    ref_builder->get_widget("display_box", display_box);
    ref_builder->get_widget("scale_alpha", scale_alpha);
    ref_builder->get_widget("scale_red", scale_red);
    ref_builder->get_widget("scale_blue", scale_blue);
    ref_builder->get_widget("scale_green", scale_green);
    ref_builder->get_widget("label_color", color_label);
    ref_builder->get_widget("btncopy",btncopy);

    // Add widgets
    display_box->pack_start(color_frame);

    // Add margin for draw_area and add widget
    draw_area.set_margin_start(5);
    draw_area.set_margin_end(5);
    draw_area.set_margin_left(5);
    draw_area.set_margin_right(5);
    draw_area.signal_draw().connect(sigc::mem_fun(*this, &ColorPanel::drawarea_draw));
    color_frame.add(draw_area);

    // Add signal for scales
    scale_alpha->signal_value_changed().connect(sigc::mem_fun(*this, &ColorPanel::scale_value_changed));
    scale_blue->signal_value_changed().connect(sigc::mem_fun(*this, &ColorPanel::scale_value_changed));
    scale_green->signal_value_changed().connect(sigc::mem_fun(*this, &ColorPanel::scale_value_changed));
    scale_red->signal_value_changed().connect(sigc::mem_fun(*this, &ColorPanel::scale_value_changed));

    // Add signal for copy color button
    btncopy->signal_clicked().connect(sigc::mem_fun(*this,&ColorPanel::btncopy_clicked));
}

void ColorPanel::scale_value_changed()
{
    // Update Color Value
    int red, green, blue, alpha;
    red = scale_red->get_value();
    green = scale_green->get_value();
    blue = scale_blue->get_value();
    alpha = scale_alpha->get_value();

    // Convert String for display
    color_str = Glib::ustring(g_strdup_printf("#%02X%02X%02X%02X  (%d,%d,%d,%d)",
                                              alpha, red, blue, green,
                                              alpha, red, green, blue));
    color_label->set_label(color_str);

    // Redraw the color
    draw_area.queue_draw();
}

bool ColorPanel::drawarea_draw(const Cairo::RefPtr<Cairo::Context> &context)
{
    // Get Color Values
    double red, green, blue, alpha;
    red = scale_red->get_value();
    green = scale_green->get_value();
    blue = scale_blue->get_value();
    alpha = scale_alpha->get_value();
    // g_print("%f %f %f %f\n", red, green, blue, alpha);

    // Set the Color and fill
    context->set_source_rgba(red / 255.0, green / 255.0, blue / 255.0, alpha / 255.0);
    context->paint();
    // context->fill();

    return false;
}

void ColorPanel::btncopy_clicked(){
    // Copy the Color String
    auto clipboard = Gtk::Clipboard::get();
    clipboard->set_text(color_str);
}

ColorPanel *ColorPanel::create()
{
    ColorPanel *panel = nullptr;

    auto builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/colorpanel.ui");
    builder->get_widget_derived("main_box", panel);

    return panel;
}