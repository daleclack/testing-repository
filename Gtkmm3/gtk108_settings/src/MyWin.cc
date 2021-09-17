#include "MyWin.hh"
#include "MyPrefs.hh"
#include "winpe.xpm"
#include <iostream>
#include <stdexcept>

MyWin::MyWin(BaseObjectType *cobject,const Glib::RefPtr<Gtk::Builder>& builder)
:Gtk::Window(cobject),
ref_builder(builder),
btnback("BackGround")
{
    int width,height;
    Glib::ustring back_filename;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf,sized;

    //Create Settings
    m_settings=Gio::Settings::create("org.gtk.daleclack");
    m_settings->bind("width",property_default_width());
    m_settings->bind("height",property_default_height());
    width=m_settings->get_int("width");
    height=m_settings->get_int("height");
    back_filename=m_settings->get_string("background");

    //Ininalize Window
    set_icon_name("org.gtk.daleclack");
    ref_builder->get_widget("btnprefs",btnprefs);
    ref_builder->get_widget("overlay",overlay);
    btnprefs->signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnprefs_clicked));

    //Add Background
    overlay->add(background);
    try{
        if(back_filename == "none"){
            pixbuf=Gdk::Pixbuf::create_from_xpm_data(winpe);
        }else{
            pixbuf=Gdk::Pixbuf::create_from_file(back_filename);
        }
        sized=pixbuf->scale_simple(width,height,Gdk::INTERP_BILINEAR);
        gtk_image_set_from_pixbuf(background.gobj(),sized->gobj());
    }
    catch(const Glib::Error& ex){
        std::cout << ex.what() << std::endl;
    }

    //Add a button
    btnback.set_halign(Gtk::ALIGN_CENTER);
    btnback.set_valign(Gtk::ALIGN_CENTER);
    overlay->add_overlay(btnback);

    //Gtkmm3 only,no need for Gtkmm4 Apps
    show_all_children();
    pixbuf.reset();
    sized.reset();
}

MyWin * MyWin::create(){
    // Load the Builder file and instantiate its widgets.
    auto refBuilder = Gtk::Builder::create_from_resource("/gtk108/window.ui");

    MyWin * window = nullptr;
    refBuilder->get_widget_derived("window", window);

    return window;
}

void MyWin::btnprefs_clicked(){
    auto prefs=MyPrefs::create(*this);
    prefs->present();
    prefs->signal_hide().connect(sigc::bind(sigc::ptr_fun(on_hide_window),prefs));
}
