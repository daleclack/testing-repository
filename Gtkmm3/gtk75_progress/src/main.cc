#include "GtkWin.hh"

int main(int argc,char **argv){
    auto app=Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    GtkWin window;
    return app->run(window);
}