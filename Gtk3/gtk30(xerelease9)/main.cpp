#include "gtkwin.h"

static void gtkmain(GtkApplication *app,gpointer user_data){
    //initalize gtk window
    GtkWin mainwin;
    mainwin.win_init(app,400,300);
    mainwin.show_all();
}

int main(int argc,char *argv[]){
    //Start a gtk application
    GtkApplication *app;
    app=gtk_application_new("com.github.daleclack.gtk28",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
