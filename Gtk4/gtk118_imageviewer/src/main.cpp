#include "MyWindow.h"

static void gtkmain(GtkApplication * app,gpointer user_data){
    MyWindow * window = my_window_new(app);
    gtk_widget_show(GTK_WIDGET(window));
}

int main(int argc,char ** argv){
    //Create a application and start
    GtkApplication * app;
    app = gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
