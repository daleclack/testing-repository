#include <gtk/gtk.h>

static void gtkmain(GtkApplication * app,gpointer user_data){
    GtkWidget * window, * media_control;
    //Initalize window
    window = gtk_application_window_new(app);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(window),400,100);
    //Create Media Stream and control
    GtkMediaStream * media_stream = gtk_media_file_new_for_resource("/org/gtk/daleclack/Yanni-Nightingale.mp3");
    media_control = gtk_media_controls_new(media_stream);
    gtk_window_set_child(GTK_WINDOW(window),media_control);
    //show the window
    gtk_widget_show(window);
}

int main(int argc,char ** argv){
    GtkApplication * app;
    app = gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
