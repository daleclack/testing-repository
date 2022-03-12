#include "ColorPicker.hh"
#include <cstdio>
#include <iostream>
#include "image_types.hh"
#include "winpe.xpm"

ColorPicker::ColorPicker()
    : Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5),
      btn_back(_("Open Image")),
      btnbox(Gtk::ORIENTATION_VERTICAL, 5),
      frame_pos(_("Position")),
      frame_css_rgba(_("rgb()/rgba() for css3")),
      frame_rgba_str(_("RGB(A) Code")),
      label_pos("(640,480)"),
      label_css_rgba("rgba(255,255,255,255)"),
      label_test(_("Color Settings And Position info")),
      label_color_str("#00000000"),
      btn_css_code(_("Copy Css3 Code")),
      btn_color_str(_("Copy RGB(A) String")),
      btn_select(_("Pick Color"))
{
    background.set_size_request(640, 480);

    // Create a pixbuf
    pixbuf = Gdk::Pixbuf::create_from_xpm_data(winpe);
    sized = pixbuf->scale_simple(640, 480, Gdk::INTERP_BILINEAR);

    // Add Button
    btn_back.set_halign(Gtk::ALIGN_CENTER);
    btn_back.set_valign(Gtk::ALIGN_CENTER);
    btn_back.signal_clicked().connect(sigc::mem_fun(*this, &ColorPicker::btnback_clicked));

    btn_css_code.set_halign(Gtk::ALIGN_CENTER);
    btn_css_code.signal_clicked().connect(sigc::mem_fun(*this, &ColorPicker::btncss_clicked));
    btn_color_str.set_halign(Gtk::ALIGN_CENTER);
    btn_color_str.signal_clicked().connect(sigc::mem_fun(*this, &ColorPicker::btncolor_clicked));

    btn_select.set_active(false);
    btn_select.set_halign(Gtk::ALIGN_CENTER);
    btn_select.signal_clicked().connect(sigc::mem_fun(*this, &ColorPicker::btnselect_clicked));

    // Add Gesture
    gesture = Gtk::GestureMultiPress::create(draw_area);
    gesture->set_button(1);
    gesture->signal_pressed().connect(sigc::mem_fun(*this, &ColorPicker::gesture_pressed));
    draw_area.set_hexpand();
    draw_area.set_vexpand();
    m_overlay.add_overlay(draw_area);

    // Set image
    gtk_image_set_from_pixbuf(background.gobj(), sized->gobj());
    get_pixel_color(320, 180);

    // Add Color and Image Button
    color_btn.set_use_alpha();
    color_btn.set_halign(Gtk::ALIGN_CENTER);
    btnbox.pack_start(label_test, Gtk::PACK_SHRINK);

    frame_pos.add(label_pos);
    btnbox.pack_start(frame_pos, Gtk::PACK_SHRINK);

    frame_css_rgba.add(label_css_rgba);
    btnbox.pack_start(frame_css_rgba, Gtk::PACK_SHRINK);

    frame_rgba_str.add(label_color_str);
    btnbox.pack_start(frame_rgba_str, Gtk::PACK_SHRINK);

    btnbox.pack_start(color_btn);
    btnbox.pack_start(btn_back);
    btnbox.pack_start(btn_select);
    btnbox.pack_start(btn_css_code);
    btnbox.pack_start(btn_color_str);
    btnbox.set_valign(Gtk::ALIGN_CENTER);

    // Add Widgets and show all
    m_overlay.add(background);
    pack_start(m_overlay);
    pack_start(btnbox);

    pixbuf.reset();
}

void ColorPicker::get_pixel_color(int x, int y)
{
    // Get Image data
    Gdk::RGBA color_set;
    int red = 0, green = 0, blue = 0, alpha = 0;
    int n_channels = sized->get_n_channels();
    int rowstride = sized->get_rowstride(); // Rows
    Glib::ustring color_str;

    // Get Pixel data
    guint8 *pixels = sized->get_pixels();

    // Get Color at specified location
    for (int i = x - 2; i <= x + 2; i++)
    {
        for (int j = y - 2; j <= y + 2; j++)
        {
            guchar *p = pixels + y * rowstride + x * n_channels;
            red += p[0];
            green += p[1];
            blue += p[2];
            if (sized->get_has_alpha())
            {
                alpha += p[4];
            }
            else
            {
                alpha += 255;
            }
        }
    }

    // Set Color to rgba
    red /= 25;
    blue /= 25;
    green /= 25;
    alpha /= 25;
    color_set.set_red_u(red * 257);
    color_set.set_blue_u(blue * 257);
    color_set.set_green_u(green * 257);
    color_set.set_alpha_u(alpha * 257);

    // Get Color set as a string
    label_css_rgba.set_label(color_set.to_string());

    // OutPut the color rgba set
    color_btn.set_rgba(color_set);

    // OutPut color Set as a Color Code
    // If the image has a alpha value, use RGBA Code, else use RGB Code
    if (sized->get_has_alpha())
    {
        color_str = Glib::ustring(g_strdup_printf("#%02X%02X%02X%02X", red, blue, green, alpha));
    }
    else
    {
        color_str = Glib::ustring(g_strdup_printf("#%02X%02X%02X", red, green, blue));
    }
    label_color_str.set_label(color_str);
}

void ColorPicker::gesture_pressed(int n_press, double x, double y)
{
    if (btn_select.get_active())
    {
        // Get Color at the position
        char pos[57];
        sprintf(pos, "(%.2f,%.2f)", x, y);
        label_pos.set_label(pos);
        get_pixel_color((int)x, (int)y);
        btn_select.set_active(false);

        // Unset custom cursor
        auto gdkwin = background.get_window();
        gdkwin->set_cursor();
    }
}

void ColorPicker::btnback_clicked()
{
    // Initalize Dialog
    dialog = Gtk::FileChooserNative::create(_("Open a image file"), *parent_win, Gtk::FILE_CHOOSER_ACTION_OPEN,
                                            _("OK"), _("Cancel"));

    // Add filter for Image files
    auto filter_image = Gtk::FileFilter::create();
    filter_image->set_name(_("Image Files"));
    if (mime_type_supported())
    {
        // For systems that supports mime type, add a mime type
        filter_image->add_mime_type("image/*");
    }
    else
    {
        // For Systems that not support mime type, use a supported globs
        for (int i = 0; supported_globs != NULL && supported_globs[i] != NULL; i++)
        {
            const char *glob = supported_globs[i];
            filter_image->add_pattern(glob);
        }
    }
    dialog->add_filter(filter_image);

    // Filter for any files
    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name(_("Any Files"));
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);

    // Link the "reponse" signal of dialog and show dialog
    dialog->signal_response().connect(sigc::mem_fun(*this, &ColorPicker::set_background));
    dialog->show();
}

void ColorPicker::set_background(int response_id)
{
    if (response_id == Gtk::RESPONSE_ACCEPT)
    {
        Glib::ustring filename = dialog->get_filename();
        pixbuf = Gdk::Pixbuf::create_from_file(filename);
        // Release memory of pixbuf "sized"
        sized.reset();
        sized = pixbuf->scale_simple(640, 480, Gdk::INTERP_BILINEAR);
        gtk_image_set_from_pixbuf(background.gobj(), sized->gobj());
        get_pixel_color(320, 180);
    }
    dialog.reset();
}

void ColorPicker::btncss_clicked()
{
    // Copy contents of label for css3 code
    auto clipboard = Gtk::Clipboard::get();
    Glib::ustring str = label_css_rgba.get_label();
    clipboard->set_text(str);
}

void ColorPicker::btncolor_clicked()
{
    // Copy contents of label for rgba code
    auto clipboard = Gtk::Clipboard::get();
    Glib::ustring str = label_color_str.get_label();
    clipboard->set_text(str);
}

void ColorPicker::btnselect_clicked()
{
    // Set a cursor for selection on image
    auto display = background.get_display();
    auto gdkwin = background.get_window();
    auto cursor = Gdk::Cursor::create(display, "crosshair");
    gdkwin->set_cursor(cursor);
}

void ColorPicker::bind_parent_win(Gtk::Window *window)
{
    parent_win = window;
}
