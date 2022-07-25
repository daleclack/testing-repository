#include "CfgConvert.hh"

int main(int argc, char **argv){
    // Create a application
    auto app = Gtk::Application::create(argc, argv, "org.gtk.daleclack");
    CfgConvert cfgwin;
    return app->run(cfgwin);
}
