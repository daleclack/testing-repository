#include "TextEditor.hh"

int main(int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv, "org.gtk.daleclack");
    TextEditor textwin;
    return app->run(textwin);
}