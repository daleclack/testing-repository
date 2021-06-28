#include "MyWin.hh"


MyWin::MyWin()
:btn_back("Change Background"),
back_dialog(*this,&back)
{
    set_icon_name("org.gtk.daleclack");
    set_default_size(640,360);
    //Add Overlay and image to the window
    add(overlay);
    overlay.add(back);
    //Add the button
    btn_back.set_halign(Gtk::ALIGN_CENTER);
    btn_back.set_valign(Gtk::ALIGN_CENTER);
    btn_back.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnback_clicked));
    overlay.add_overlay(btn_back);
    //Set Default Background
    back_dialog.default_background();
    //Show all children
    show_all_children();
}

void MyWin::btnback_clicked(){
   back_dialog.show_all();
}

MyWin::~MyWin(){
}
