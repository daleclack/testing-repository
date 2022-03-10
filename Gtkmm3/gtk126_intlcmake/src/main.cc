#include "MyWin.hh"
#define GETTEXT_PACKAGE "gtk126"
#define PROGRAMNAME_LOCALEDIR "./po"

int main(int argc,char ** argv){
    // Initalize gettext
    //setlocale(LC_ALL,"");
    bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);

    // Create application and run
    auto app = Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    MyWin window;
    return app->run(window);
}
