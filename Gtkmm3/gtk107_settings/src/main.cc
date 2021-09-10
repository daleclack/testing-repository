#include "MyWin.hh"

int main(int argc,char **argv){
    //Initalize env
    Glib::setenv("GSETTINGS_SCHEMA_DIR",".",false);

    //Create a application and run
    auto app=Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    auto window=MyWin::create();

    return app->run(*window);
}