#pragma once

#include <gtkmm.h>
#include <glibmm/i18n.h>

class ColorPicker : public Gtk::Box
{
public:
    ColorPicker();
    void bind_parent_win(Gtk::Window * window);

private:
    // Parent Window
    Gtk::Window * parent_win;

    // Child Widgets
    Gtk::Overlay m_overlay;
    Gtk::Button btn_back;
    Gtk::Image background;
    Gtk::Box btnbox;
    Gtk::Frame frame_pos, frame_css_rgba, frame_rgba_str;
    Gtk::Label label_pos, label_css_rgba, label_test, label_color_str;
    Gtk::ColorButton color_btn;
    Gtk::Button btn_css_code, btn_color_str;
    Gtk::ToggleButton btn_select;
    Gtk::DrawingArea draw_area;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf;
    Glib::RefPtr<Gdk::Pixbuf> sized;

    // Get Mouse Position
    Glib::RefPtr<Gtk::GestureMultiPress> gesture;

    // Signal Handlers
    Glib::RefPtr<Gtk::FileChooserNative> dialog;
    void get_pixel_color(int x, int y);
    void btnback_clicked();
    void set_background(int reponse_id);
    void gesture_pressed(int n_press, double x, double y);
    void btncss_clicked();
    void btncolor_clicked();
    void btnselect_clicked();
};