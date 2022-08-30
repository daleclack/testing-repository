#include "MineSweeper.hh"

int main(int argc, char **argv){
    // Create a application and run
    auto app = Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    MineSweeper window;
    return app->run(window);
}