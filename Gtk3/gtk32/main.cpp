#include <gtk/gtk.h>
#include "winpe.xpm"

void win1_activate(GtkWidget *widget,gpointer data){
    GtkBuilder *builder=gtk_builder_new_from_file("window1.ui");
    GObject *window1=gtk_builder_get_object(builder,"window1");
    //Window minimize button
    GObject *btn_minimize=gtk_builder_get_object(builder,"btn_mini");
    g_signal_connect_swapped(btn_minimize,"clicked",G_CALLBACK(gtk_widget_hide),window1);
    //Window close button
    GObject *btnclose=gtk_builder_get_object(builder,"btn_close");
    g_signal_connect_swapped(btnclose,"clicked",G_CALLBACK(g_object_unref),window1);
    g_signal_connect_swapped(btnclose,"clicked",G_CALLBACK(gtk_widget_destroy),window1);
    //button box signal
    g_signal_connect_swapped(G_OBJECT(data),"clicked",G_CALLBACK(gtk_widget_show),window1);
    gtk_widget_show(GTK_WIDGET(window1));
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkBuilder *builder=gtk_builder_new_from_file("window.ui");
    GObject *window=gtk_builder_get_object(builder,"window");
    gtk_application_add_window(app,GTK_WINDOW(window));
    //Background config
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_xpm_data(winpe);
    GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,640,360,GDK_INTERP_BILINEAR);
    GObject *image=gtk_builder_get_object(builder,"image");
    gtk_image_set_from_pixbuf(GTK_IMAGE(image),sized);
    //Window Icon
    GdkPixbuf *icon=gdk_pixbuf_new_from_file("icon.jpg",NULL);
    gtk_window_set_icon(GTK_WINDOW(window),icon);
    //"Win1" button in menu and button box
    GObject *btnwin1=gtk_builder_get_object(builder,"btn_win1");
    GObject *win1=gtk_builder_get_object(builder,"win1");
    g_signal_connect(btnwin1,"activate",G_CALLBACK(win1_activate),(gpointer)win1);
    //"Exit" button
    GObject *btnexit=gtk_builder_get_object(builder,"btn_exit");
    g_signal_connect_swapped(btnexit,"activate",G_CALLBACK(gtk_widget_destroy),window);

    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    app=gtk_application_new("com.github.daleclack.gtk32",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}