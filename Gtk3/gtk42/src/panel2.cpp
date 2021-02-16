#include <cstdlib>
#include <thread>
#include "panel2.h"

void add_leftpanel(GtkBuilder *builder,GtkFixed *fixed){
    //Get Left panel
    GtkBuilder *panel2=gtk_builder_new_from_file("res/leftpanel.ui");
    GObject *panel=gtk_builder_get_object(panel2,"left_panel");
    //Set start button and image
    GObject *btn_image=gtk_builder_get_object(panel2,"btn_image");
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_file("res/icon.png",NULL);
    GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,40,40,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(btn_image),sized);
    //vlc exec button for linux
    GObject *btnvlc=gtk_builder_get_object(panel2,"btnvlc");
    g_signal_connect(btnvlc,"clicked",G_CALLBACK(btnvlc_clicked),NULL);
    //Start Gedit Text Editor
    GObject *btngedit=gtk_builder_get_object(panel2,"btngedit");
    g_signal_connect(btngedit,"clicked",G_CALLBACK(btngedit_clicked),NULL);
    gtk_fixed_put(fixed,GTK_WIDGET(panel),0,25);
    g_object_unref(pixbuf);
    g_object_unref(sized);
}   

void btnvlc_clicked(GtkWidget *widget,gpointer data){
    std::thread first(system,"vlc");
    first.detach();
}

void btngedit_clicked(GtkWidget *widget,gpointer data){
    std::thread second(system,"gedit");
    second.detach();
}
