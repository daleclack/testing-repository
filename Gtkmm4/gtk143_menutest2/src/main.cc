#include "MenuWin.hh"

/*
This is a test for fake global menu,
the project exist because the GtkPopoverMenuBar can't read by appmenu-gtk module.
I don't know the reason for that, but it may be a interesting idea to 
add fake global menu for My Gtk UI.
Written by dale clack, 2022/12/5
*/

int main(int argc, char **argv){
    // Create a application
    auto app = Gtk::Application::create("org.gtk.daleclack");

    // Create a window and run the application
    app->make_window_and_run<MenuWin>(argc, argv);
}