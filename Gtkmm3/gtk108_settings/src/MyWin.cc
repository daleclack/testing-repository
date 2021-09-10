#include "MyWin.hh"

MyWin::MyWin(BaseObjectType *cobject,const Glib::RefPtr<Gtk::Builder>& builder)
:Gtk::Window(cobject),
ref_builder(builder)
{
    m_settings=Gio::Settings::create("org.gtk.daleclack");
    m_settings->bind("width",property_default_width());
    m_settings->bind("height",property_default_height());
    set_icon_name("org.gtk.daleclack");
}

MyWin * MyWin::create(){
    // Load the Builder file and instantiate its widgets.
    auto refBuilder = Gtk::Builder::create_from_resource("/gtk108/window.ui");

    MyWin * window = nullptr;
    refBuilder->get_widget_derived("window", window);

    return window;
}

MyWin::~MyWin(){
}
