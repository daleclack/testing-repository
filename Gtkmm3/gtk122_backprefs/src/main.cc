#include "MyWin.hh"

int main(int argc,char ** argv){
    // Create application and run
    auto app = Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    MyWin window;
    return app->run(window);
}
