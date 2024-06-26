#pragma once

#include <gtkmm.h>
#include "MyImage.hh"

class MyWin : public Gtk::ApplicationWindow
{
public:
    MyWin();

private:
    // Child widgets
    Gtk::ScrolledWindow sw;
    MyImage image_area;
    Gtk::Box main_box, btnbox;
    Gtk::Button btnopen;
    Gtk::Scale scale;
    Gtk::Overlay overlay;
    Glib::RefPtr<Gtk::Adjustment> m_adjustment, hadjustment, vadjustment;
    Glib::RefPtr<Gtk::FileChooserNative> dialog;

    // Gesture control
    Glib::RefPtr<Gtk::GestureDrag> gesture_drag;
    Glib::RefPtr<Gtk::GestureMultiPress> gesture_click;
    void drag_begin(double x, double y);
    void drag_update(double x, double y);
    void drag_end(double x, double y);
    void move_to(double x, double y);

    // Menu for image control
    Gtk::PopoverMenu popover;
    void press(int n_press, double x, double y);

    // Signal Handlers
    void btnopen_clicked();
    void dialog_response(int response_id);
    void scale_changed();
    void image_zoom_in();
    void image_zoom_out();
    void image_zoom_reset();
};
