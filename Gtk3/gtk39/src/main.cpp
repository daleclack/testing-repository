#include "gtk/gtk.h"

static void gtkmain(GtkApplication *app,gpointer user_data){
    //Main window
    GtkBuilder *builder=gtk_builder_new_from_file("res/window.ui");
    GObject *window=gtk_builder_get_object(builder,"window");
    gtk_application_add_window(app,GTK_WINDOW(window));
    //"Exit" button
    GObject *btn_exit=gtk_builder_get_object(builder,"btnexit");
    g_signal_connect_swapped(btn_exit,"clicked",G_CALLBACK(gtk_widget_destroy),window);
    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    app=gtk_application_new("com.github.daleclack.gtk39",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
