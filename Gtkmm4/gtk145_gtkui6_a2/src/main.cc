#include "MainWin.hh"

/*
The test application for My GtkUi 6.0, 
In this version of My Gtk UI, more features will be added.
Because the Gtkmm4 has major changes with the Gtkmm3,
so some test is needed.
This is the first test, hello Gtkmm4!
Written by dale clack, 2023/1/15
*/

int main(int argc, char **argv){
    // Create a application
    auto app = Gtk::Application::create("org.gtk.daleclack");

    // Create a window and run the application
    app->make_window_and_run<MainWin>(argc, argv);
}