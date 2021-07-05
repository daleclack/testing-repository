#include "MyWin.hh"

int main(int argc,char **argv){
    auto app=Gtk::Application::create("org.gtk.daleclack");
    return app->make_window_and_run<MyWin>(argc,argv);
}
