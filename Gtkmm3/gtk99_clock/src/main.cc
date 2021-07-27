#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "Clock.hh"

int main(int argc,char **argv){
    auto app=Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    
    //Initalize window and a clock
    Gtk::Window window;
    window.set_icon_name("org.gtk.daleclack");
    window.set_title("Clock");
    Clock clock1;
    window.add(clock1);
    window.show_all();

    return app->run(window);
}
