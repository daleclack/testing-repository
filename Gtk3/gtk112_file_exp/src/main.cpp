#include "FileWindow.h"

static void gtkmain(GtkApplication *app,gpointer user_data){
    FileWindow * window;
    window = file_window_new(app);
    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
