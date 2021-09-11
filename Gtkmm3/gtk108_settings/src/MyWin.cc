#include "MyWin.hh"
#include "MyPrefs.hh"

MyWin::MyWin(BaseObjectType *cobject,const Glib::RefPtr<Gtk::Builder>& builder)
:Gtk::Window(cobject),
ref_builder(builder)
{
    //Create Settings
    m_settings=Gio::Settings::create("org.gtk.daleclack");
    m_settings->bind("width",property_default_width());
    m_settings->bind("height",property_default_height());

    //Ininalize Window
    set_icon_name("org.gtk.daleclack");
    ref_builder->get_widget("btnprefs",btnprefs);
    btnprefs->signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnprefs_clicked));
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
    prefs->signal_hide().connect(sigc::bind(sigc::mem_fun(*this,&MyWin::on_hide_window),prefs));
}

void MyWin::on_hide_window(Gtk::Window* window){
    delete window;
}
