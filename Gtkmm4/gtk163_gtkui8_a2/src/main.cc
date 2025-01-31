#include "MainWin.hh"

int main(int argc, char **argv)
{
    // Create a application and add a window
    auto app = Gtk::Application::create("org.gtk.daleclack");
    MainWin *win = MainWin::create();
    app->register_application();
    app->add_window(*win);
    win->present();
    return app->run(argc, argv);
}