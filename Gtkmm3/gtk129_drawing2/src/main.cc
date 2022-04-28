#include "drawing.hh"

int main(int argc,char **argv){
    auto app=Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    Drawing window;
    return app->run(window);
}
