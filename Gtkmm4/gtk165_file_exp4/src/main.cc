#include "FileWindow.hh"

int main(int argc, char **argv)
{
    // Create an application instance and run
    auto app = Gtk::Application::create("org.gtk.daleclack");
    return app->make_window_and_run<FileWindow>(argc, argv);
}