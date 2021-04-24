#include <gtkmm.h>
#include "src/winpe.xpm"

int main(int argc,char **argv){
    auto app=Gtk::Application::create(argc,argv,"org.gtkmm.test");
    Gtk::Window window;
    window.set_default_size(640,360);
    window.set_icon_name("org.gtk.daleclack");
    window.set_title("Gtkmm 3 test");
    Glib::RefPtr<Gdk::Pixbuf> pixbuf=Gdk::Pixbuf::create_from_xpm_data(winpe);
    Glib::RefPtr<Gdk::Pixbuf> sized=pixbuf->scale_simple(640,360,Gdk::InterpType::INTERP_BILINEAR);
    Gtk::Image image1 (sized);
    window.add(image1);
    window.show_all();
    return app->run(window);
}
