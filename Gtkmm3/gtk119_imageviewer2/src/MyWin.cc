#include "MyWin.hh"

MyWin::MyWin()
:main_box(Gtk::ORIENTATION_VERTICAL,5),
btnbox(Gtk::ORIENTATION_HORIZONTAL,5),
btnopen("Open Image")
{
    //Add Widgets
    set_default_size(800,450);
    set_icon_name("org.gtk.daleclack");
    
    //Scrolled Window
    sw.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    sw.add(image_area);
    main_box.pack_start(sw);

    //Initalize Scale
    m_adjustment = Gtk::Adjustment::create(1.0,0.1,10.0,0.1,0.1);
    scale.set_default_direction(Gtk::TEXT_DIR_LTR);
    scale.set_adjustment(m_adjustment);
    scale.signal_value_changed().connect(sigc::mem_fun(*this,&MyWin::scale_changed));

    //Add control widgets
    btnbox.pack_start(scale);
    btnbox.pack_start(btnopen,Gtk::PACK_SHRINK);
    main_box.pack_start(btnbox,Gtk::PACK_SHRINK);
    btnopen.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnopen_clicked));

    //Add Gesture
    gesture_drag = Gtk::GestureDrag::create(image_area);
    gesture_drag->set_button(GDK_BUTTON_PRIMARY);
    //gesture_drag->signal_drag_begin().connect(sigc::mem_fun(*this,&MyWin::drag_begin));
    gesture_drag->signal_drag_update().connect(sigc::mem_fun(*this,&MyWin::drag_update));
    gesture_drag->signal_drag_end().connect(sigc::mem_fun(*this,&MyWin::drag_end));

    add(main_box);
    show_all_children();
}

void MyWin::btnopen_clicked(){
    //Create a file open dialog
    dialog = Gtk::FileChooserNative::create("Open a image File",*this,Gtk::FILE_CHOOSER_ACTION_OPEN,
                                            "OK","Cancel");
    
    dialog->signal_response().connect(sigc::mem_fun(*this,&MyWin::dialog_response));

    dialog->show();
}

void MyWin::dialog_response(int response_id){
    if(response_id == Gtk::RESPONSE_ACCEPT){
        //Show the image in a drawing area
        auto filename = dialog->get_filename();
        auto pixbuf = Gdk::Pixbuf::create_from_file(filename);
        image_area.set_pixbuf(pixbuf);
        pixbuf.reset();
        //Set Adjustments
        if(hadjustment){
            hadjustment.reset();
            vadjustment.reset();
        }
        hadjustment = sw.get_hadjustment();
        vadjustment = sw.get_vadjustment();
    }

    dialog.reset();
}

void MyWin::scale_changed(){
    double value = scale.get_value();
    g_print("%f\n",value);
    image_area.scale_draw(value);
}

void MyWin::drag_begin(double x,double y){
    //g_print("drag begins\n");
    //move_to(x,y);
}

void MyWin::drag_update(double x,double y){
    //g_print("drag updated\n");
    move_to(x,y);
}

void MyWin::drag_end(double x,double y){
    //g_print("drag ended\n");
    move(x,y);
}

void MyWin::move_to(double x,double y){
    g_print("%f %f\n",x,y);
}
