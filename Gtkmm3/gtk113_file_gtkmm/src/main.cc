#include "FileWindow.hh"

int main(int argc,char **argv){
    auto app = Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    FileWindow window;
    return app->run(window);
}
