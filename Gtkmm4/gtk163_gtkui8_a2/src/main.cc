#include "MainWin.hh"

int main(int argc, char **argv)
{
    // Create a application and add a window
    auto app = Gtk::Application::create("org.gtk.daleclack");
    MainWin *win = MainWin::create();

    // Add the window to the application
    app->register_application();
    app->add_window(*win);

    // Show the window and start the application
    win->present();
    return app->run(argc, argv);
}