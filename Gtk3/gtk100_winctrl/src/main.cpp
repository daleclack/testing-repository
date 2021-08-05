#include <gtk/gtk.h>
#include "WinBtn.h"
#include "winpe.xpm"

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window, *back, *overlay;
    WinBtn * win_btn;

    //Create window
    window=gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window),640,360);
    gtk_window_set_title(GTK_WINDOW(window),"Minimize Test");
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");

    //Create overlay
    overlay=gtk_overlay_new();

    //Get Background
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_xpm_data(winpe);
    GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,640,360,GDK_INTERP_BILINEAR);
    back=gtk_image_new_from_pixbuf(sized);
    gtk_container_add(GTK_CONTAINER(overlay),back);
    g_object_unref(pixbuf);
    g_object_unref(sized);

    //Initalize Panel
    win_btn=win_btn_new();
    win_btn_set_application(win_btn,app);
    gtk_button_set_relief(GTK_BUTTON(win_btn),GTK_RELIEF_NONE);
    gtk_button_set_label(GTK_BUTTON(win_btn),"Minimize");

    gtk_widget_set_halign(GTK_WIDGET(win_btn),GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(win_btn),GTK_ALIGN_CENTER);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay),GTK_WIDGET(win_btn));
    
    //Pack Boxs
    gtk_container_add(GTK_CONTAINER(window),overlay);
    gtk_widget_show_all(window);
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
