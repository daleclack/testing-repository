#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "MyArea.hh"

int main(int argc,char **argv){
    auto app=Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    //Create a window
    Gtk::Window window;
    MyArea area1;
    window.add(area1);
    window.show_all();

    return app->run(window);
}
