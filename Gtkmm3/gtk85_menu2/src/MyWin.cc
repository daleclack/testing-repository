#include "MyWin.hh"

MyWin::MyWin(){
    //Initalize Window
    set_icon_name("org.gtk.daleclack");
    set_default_size(800,450);
    overlay.add_overlay(draw_area);
    //Initalize menu
    menu_builder=Gtk::Builder::create_from_file("../res/appmenu.xml");
    auto object=menu_builder->get_object("app-menu");
    auto gmenu=Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
    //Set Popover Menu
    popover.bind_model(gmenu);
    popover.set_relative_to(draw_area);
    //Set Gesture
    gesture=Gtk::GestureMultiPress::create(draw_area);
    gesture->set_button(3);
    gesture->signal_pressed().connect(sigc::mem_fun(*this,&MyWin::btn_pressed));
    add(overlay);
    show_all();
}

void MyWin::btn_pressed(int n_press,double x,double y){
    Gdk::Rectangle point{(int)x,(int)y,1,1};
    popover.set_pointing_to(point);
    popover.popup();
}

MyWin::~MyWin(){
}
