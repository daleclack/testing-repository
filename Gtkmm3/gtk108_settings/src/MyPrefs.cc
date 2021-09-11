#include "MyPrefs.hh"

MyPrefs::MyPrefs(BaseObjectType* cobject,const Glib::RefPtr<Gtk::Builder>& builder)
:Gtk::Dialog(cobject),
m_builder(builder)
{
    //Get Widgets
    m_builder->get_widget("width_spin",m_width);
    m_builder->get_widget("height_spin",m_height);

    //Create Settings
    m_settings=Gio::Settings::create("org.gtk.daleclack");
    m_settings->bind("width",m_width->property_value());
    m_settings->bind("height",m_height->property_value());
}

MyPrefs * MyPrefs::create(Gtk::Window& parent){
    //Load the builder file and create dialog
    auto ref_builder=Gtk::Builder::create_from_resource("/gtk108/prefs.ui");

    MyPrefs* dialog=nullptr;
    ref_builder->get_widget_derived("prefs",dialog);
    dialog->set_transient_for(parent);

    return dialog;
}
