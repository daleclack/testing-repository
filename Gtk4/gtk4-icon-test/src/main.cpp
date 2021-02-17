#include <gtk/gtk.h>

static void gtkmain(GtkApplication *app,gpointer data){
    GtkWidget *window;
    window=gtk_application_window_new(app);
    gtk_widget_show(window);
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    int status;
    app=gtk_application_new("org.gtk.Demo4",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    return status;
}
