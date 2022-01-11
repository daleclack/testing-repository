#include "MyWin.hh"

int main(int argc,char ** argv){
    //Create a application and run
    auto app = Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    auto win = MyWin::create();
    return app->run(*win);
}
