#include <gtkmm.h>

int main(int argc,char **argv){
    auto app=Gtk::Application::create(argc,argv,"org.gtkmm.test");
    Gtk::Window window;
    window.set_default_size(200,200);
    window.set_icon_name("org.gtk.daleclack");
    return app->run(window);
}
