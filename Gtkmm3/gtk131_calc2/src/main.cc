#include "CalcApp.hh"

int main(int argc,char **argv){
    auto app = Gtk::Application::create(argc,argv,"org.gtk.daleclack");

    auto window = CalcApp::create();

    return app->run(*window);
}