#include <gtk/gtk.h>
#include "background.h"

static void gtkmain(GtkApplication *app,gpointer user_data){
    //Get main window
    GtkBuilder *builder=gtk_builder_new_from_file("res/window.ui");
    GObject *window=gtk_builder_get_object(builder,"window");
    //Get button for change background
    GObject *btn_back=gtk_builder_get_object(builder,"btnback");
    g_signal_connect(btn_back,"clicked",G_CALLBACK(fileopen),builder);
    //default background
    default_background(builder);
    //Add window to the application and show
    gtk_application_add_window(app,GTK_WINDOW(window));
    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    int status;
    app=gtk_application_new("com.github.daleclack.gtk42",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    return status;
}
