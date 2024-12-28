#include "MainWin.hh"

int main(int argc, char **argv)
{
    auto app = Gtk::Application::create("org.gtk.daleclack");
    app->make_window_and_run<MainWin>(argc, argv);
}