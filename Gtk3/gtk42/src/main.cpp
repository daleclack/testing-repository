#include <gtk/gtk.h>
#include "background.h"
#include "winconf.h"
#include "panel1.h"
#include "panel2.h"

static void gtkmain(GtkApplication *app,gpointer user_data){
    //Get main window
    int width=640,height=360;
    get_config(&width,&height);
    //GtkBuilder *builder=gtk_builder_new_from_file("res/window.ui");
    GtkBuilder *builder=gtk_builder_new_from_resource("/gtk42/window.ui");
    GObject *window=gtk_builder_get_object(builder,"window");
    gtk_window_set_default_size(GTK_WINDOW(window),width,height);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");

    //Home button
    GObject *img_home=gtk_builder_get_object(builder,"image1");
    gtk_image_set_from_resource(GTK_IMAGE(img_home),"/gtk42/user-home.png");
    
    //Get button for change background(moved to panel 1)
    /*GObject *btn_back=gtk_builder_get_object(builder,"btnback");
    g_signal_connect(btn_back,"clicked",G_CALLBACK(fileopen),builder);*/
    
    //Config button(moved to panel 1)
    /*GObject *btn_conf=gtk_builder_get_object(builder,"btnset");
    g_signal_connect(btn_conf,"clicked",G_CALLBACK(conf_dialog),builder);*/
    //default background

    default_background(builder);
    //Add a top panel with timer
    GObject *fixed=gtk_builder_get_object(builder,"fixed");
    add_toppanel(builder,GTK_FIXED(fixed));
    add_leftpanel(builder,GTK_FIXED(fixed));
    //Add window to the application and show
    gtk_application_add_window(app,GTK_WINDOW(window));
    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    int status;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    return status;
}
