#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

static void gtkmain(GtkApplication * app, gpointer user_data){
    //Initalize window
    GtkWidget * window = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window),1280,720);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");

    //Initalize webkit
    GtkWidget * webkit = webkit_web_view_new();
    webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webkit),"https://docs.gtk.org");
    gtk_container_add(GTK_CONTAINER(window),webkit);

    gtk_widget_show_all(window);
}

int main(int argc,char ** argv){
    GtkApplication * app;
    app = gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}