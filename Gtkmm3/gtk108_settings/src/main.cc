#include "MyWin.hh"

int main(int argc,char **argv){
    //Initalize env
    Glib::setenv("GSETTINGS_SCHEMA_DIR",".",false);

    //Create a application and run
    auto app=Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    auto window=MyWin::create();
    window->signal_hide().connect(sigc::bind(sigc::ptr_fun(on_hide_window),window));

    return app->run(*window);
}