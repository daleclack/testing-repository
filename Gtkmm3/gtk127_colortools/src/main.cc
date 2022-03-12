#include "MyWin.hh"
#define GETTEXT_PACKAGE "gtk127"
#define PROGRAMNAME_LOCALEDIR "./po"

int main(int argc,char ** argv){
    //Enable Gettext
    bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);

    // Create the application
    auto app = Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    auto window = MyWin::create();
    return app->run(*window);
}
