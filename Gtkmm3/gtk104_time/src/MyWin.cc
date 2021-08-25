#include "MyWin.hh"
#include "winpe.xpm"
#include <ctime>

MyWin::MyWin()
{
    set_icon_name("org.gtk.daleclack");
    myconnection=Glib::signal_timeout().connect(sigc::mem_fun(*this,&MyWin::on_timeout),1000);
}

bool MyWin::on_timeout(){
    time_t t;
    t=time(NULL);
    struct tm *local;
    local=localtime(&t);
    if(local->tm_hour == 10 && local->tm_min == 50){
        Gtk::MessageDialog dialog("Time out!");
        dialog.run();
    }
    return true;
}
