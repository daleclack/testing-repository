#include "GtkWin.hh"

MyWin::MyWin()
:m_paned(Gtk::ORIENTATION_VERTICAL)
{
    //Initalize window
    set_default_size(400,300);
    set_icon_name("org.gtk.daleclack");
    //Initalize frames
    frame1.set_size_request(200,100);
    frame1.set_label("Frame 1");
    frame2.set_size_request(200,300);
    frame2.set_label("Frame 2");
    m_paned.add1(frame1);
    m_paned.add2(frame2);
    add(m_paned);
    show_all();
}

MyWin::~MyWin(){
}