#include "MyWin.hh"
#define bin_str 6

int main(int argc,char **argv){
    //Get binary dir
    const char * src = *argv;
    int len = strlen(src); //argv[0]
    char * tmp = (char*)malloc(len);
#ifdef _WIN32
    strncpy(tmp,src,len-bin_str-4);
    tmp[len-bin_str-4]='\0';
#else
    strncpy(tmp,src,len-bin_str);
    tmp[len-bin_str]='\0';
#endif

    //Initalize env
    Glib::setenv("GSETTINGS_SCHEMA_DIR",tmp,false);

    free(tmp);

    //Create a application and run
    auto app=Gtk::Application::create(argc,argv,"org.gtk.daleclack");
    auto window=MyWin::create();
    window->signal_hide().connect(sigc::bind(sigc::ptr_fun(on_hide_window),window));

    return app->run(*window);
}