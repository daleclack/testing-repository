#include "MyWin.hh"
#include "winpe.xpm"

MyWin::MyWin()
:btnset("Setting"),
dialog1(*this)
{
    //Initalize window
    int width=640,height=360;
    set_icon_name("org.gtk.daleclack");
    set_title("CfgFile Test2");

    //Add Image and button
    m_overlay.add(m_back);
    btnset.set_halign(Gtk::ALIGN_CENTER);
    btnset.set_valign(Gtk::ALIGN_CENTER);
    m_overlay.add_overlay(btnset);
    add(m_overlay);

    //Read Config File,else use default background
    std::string filename("config");
    if(readCfgFile(filename,configs)){
        std::string backname=configs["background"];
        if(backname.empty()){
            default_background();
        }else{
            auto pixbuf=Gdk::Pixbuf::create_from_file(backname);
            auto sized=pixbuf->scale_simple(width,height,Gdk::INTERP_BILINEAR);
            gtk_image_set_from_pixbuf(m_back.gobj(),sized->gobj());
            pixbuf.reset();
            sized.reset();
        }
    }else{
        default_background();
    }
    
        
    dialog1.set_config(&configs,&m_back);
    btnset.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnset_clicked));

    //Show Everything
    show_all_children();
}

void MyWin::btnset_clicked(){
    dialog1.show_all();
}

void MyWin::default_background(){
    auto pixbuf=Gdk::Pixbuf::create_from_xpm_data(winpe);
    auto sized=pixbuf->scale_simple(640,360,Gdk::INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(m_back.gobj(),sized->gobj());
    pixbuf.reset();
    sized.reset();
}
