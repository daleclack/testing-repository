#include "GtkWin.hh"

int main(int argc,char **argv){
    auto app=Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    //Create a window and run it
    GtkWin window;
    return app->run(window);
}