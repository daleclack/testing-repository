#include "MenuWin.hh"

int main(int argc, char **argv){
    // Create a application
    auto app = Gtk::Application::create("org.gtk.daleclack");

    // Create a window and run the application
    app->make_window_and_run<MenuWin>(argc, argv);
}