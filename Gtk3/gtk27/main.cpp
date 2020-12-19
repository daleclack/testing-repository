#include "GtkClass.h"
#include "winclass.h"

static void activate(GtkApplication *app,gpointer user_data){
    GtkMain win_main;
    win_main.init(app);
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    int status;
    app=gtk_application_new("com.github.gtk27",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    return status;
}
