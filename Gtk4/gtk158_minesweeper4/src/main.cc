#include "MineSweeper.hh"

int main(int argc, char **argv){
    // Create a application and run
    auto app = Gtk::Application::create("org.gtk.daleclack");
    
    return app->make_window_and_run<MineSweeper>(argc,argv);
}
