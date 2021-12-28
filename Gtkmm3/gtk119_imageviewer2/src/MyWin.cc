#include "MyWin.hh"

MyWin::MyWin()
    : main_box(Gtk::ORIENTATION_VERTICAL, 5),
      btnbox(Gtk::ORIENTATION_HORIZONTAL, 5),
      btnopen("Open Image")
{
    // Add Widgets
    set_default_size(800, 450);
    set_icon_name("org.gtk.daleclack");

    // Scrolled Window
    sw.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    sw.add(image_area);
    main_box.pack_start(sw);

    // Initalize Scale
    m_adjustment = Gtk::Adjustment::create(1.0, 0.1, 10.0, 0.1, 0.1);
    scale.set_default_direction(Gtk::TEXT_DIR_LTR);
    scale.set_adjustment(m_adjustment);
    scale.signal_value_changed().connect(sigc::mem_fun(*this, &MyWin::scale_changed));

    // Add control widgets
    btnbox.pack_start(scale);
    btnbox.pack_start(btnopen, Gtk::PACK_SHRINK);
    main_box.pack_start(btnbox, Gtk::PACK_SHRINK);
    btnopen.signal_clicked().connect(sigc::mem_fun(*this, &MyWin::btnopen_clicked));

    // Add Drag Gesture
    gesture_drag = Gtk::GestureDrag::create(image_area);
    gesture_drag->set_button(GDK_BUTTON_PRIMARY);
    gesture_drag->signal_drag_update().connect(sigc::mem_fun(*this, &MyWin::drag_update));
    gesture_drag->signal_drag_end().connect(sigc::mem_fun(*this, &MyWin::drag_end));

    gesture_click = Gtk::GestureMultiPress::create(image_area);
    gesture_click->set_button(GDK_BUTTON_SECONDARY);
    gesture_click->signal_pressed().connect(sigc::mem_fun(*this, &MyWin::press));

    // Add Menu
    auto builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/appmenu.xml");
    auto object = builder->get_object("model");
    auto gmenu = Glib::RefPtr<Gio::MenuModel>::cast_dynamic(object);
    popover.bind_model(gmenu);
    popover.set_relative_to(image_area);

    // Add actions for menu
    add_action("zoom_in", sigc::mem_fun(*this, &MyWin::image_zoom_in));
    add_action("zoom_out", sigc::mem_fun(*this, &MyWin::image_zoom_out));
    add_action("zoom_reset", sigc::mem_fun(*this, &MyWin::image_zoom_reset));

    overlay.add(main_box);
    add(overlay);
    show_all_children();
}

void MyWin::btnopen_clicked()
{
    // Create a file open dialog
    dialog = Gtk::FileChooserNative::create("Open a image File", *this, Gtk::FILE_CHOOSER_ACTION_OPEN,
                                            "OK", "Cancel");

    dialog->signal_response().connect(sigc::mem_fun(*this, &MyWin::dialog_response));

    dialog->show();
}

void MyWin::dialog_response(int response_id)
{
    if (response_id == Gtk::RESPONSE_ACCEPT)
    {
        // Show the image in a drawing area
        auto filename = dialog->get_filename();
        auto pixbuf = Gdk::Pixbuf::create_from_file(filename);
        image_area.set_pixbuf(pixbuf);
        pixbuf.reset();
        // Set Adjustments
        if (hadjustment)
        {
            hadjustment.reset();
            vadjustment.reset();
        }
        hadjustment = sw.get_hadjustment();
        vadjustment = sw.get_vadjustment();
    }

    dialog.reset();
}

void MyWin::scale_changed()
{
    // Get Value of scale widget and scale image
    double value = scale.get_value();
    // g_print("%f\n", value);
    image_area.scale_draw(value);
}

void MyWin::press(int n_press, double x, double y)
{
    // Set Popover to the position of mouse and show
    popover.set_pointing_to(Gdk::Rectangle(x, y, 1, 1));
    popover.popup();
}

void MyWin::drag_update(double x, double y)
{
    // g_print("drag updated\n");
    move_to(x, y);
}

void MyWin::drag_end(double x, double y)
{
    // g_print("drag ended\n");
    move(x, y);
}

void MyWin::move_to(double x, double y)
{
    // g_print("%f %f\n",x,y);
    // Get Current Value
    double h_value = hadjustment->get_value();
    double v_value = vadjustment->get_value();
    // Get Max Value for movement
    double hmaxvalue = hadjustment->get_upper(); //- hadjustment->get_page_size();
    double vmaxvalue = hadjustment->get_upper(); //- vadjustment->get_page_size();
    h_value -= x;
    v_value -= y;
    // Before movement, make sure the value is vaild
    if (h_value < 0)
    {
        h_value = 0;
    }
    if (h_value > hmaxvalue)
    {
        h_value = hmaxvalue;
    }
    // Before movement, make sure the value is vaild
    if (v_value < 0)
    {
        v_value = 0;
    }
    if (v_value > vmaxvalue)
    {
        v_value = vmaxvalue;
    }
    // Perform movement
    hadjustment->set_value(h_value);
    vadjustment->set_value(v_value);
}

void MyWin::image_zoom_in()
{
    // Scale 0.1 More
    double value = scale.get_value();
    value += 0.1;
    scale.set_value(value);
    image_area.scale_draw(value);
}

void MyWin::image_zoom_out()
{
    // Scale 0.1 Less
    double value = scale.get_value();
    value -= 0.1;
    scale.set_value(value);
    image_area.scale_draw(value);
}

void MyWin::image_zoom_reset()
{
    // Scale as 1:1
    scale.set_value(1.0);
    image_area.scale_draw(1.0);
}
