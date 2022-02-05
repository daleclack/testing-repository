#include "MyWin.hh"

int main(int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv, "org.gtk.daleclack");
    auto window = MyWin::create();
    return app->run(*window);
}
