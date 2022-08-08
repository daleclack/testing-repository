#include "MediaPlayer.hh"

int main(int argc, char **argv)
{
    // Create a application
    auto app = Gtk::Application::create("org.gtk.daleclack");
    app->make_window_and_run<MediaPlayer>(argc, argv);
}
