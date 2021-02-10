#include <gtk/gtk.h>
#include "res/winpe.xpm"

gboolean window_resize(GtkWidget *widget,GdkEvent *event,GtkBuilder *builder){
    //Get window size
    gint width,height;
    gtk_window_get_size(GTK_WINDOW(widget),&width,&height);
    GObject *image=gtk_builder_get_object(builder,"background");
    GdkPixbuf *pixbuf,*sized;
    pixbuf=gdk_pixbuf_new_from_xpm_data(winpe);
    sized=gdk_pixbuf_scale_simple(pixbuf,width,height,GDK_INTERP_BILINEAR);
    gtk_widget_set_size_request(GTK_WIDGET(image),width,height);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image),sized);
    g_object_unref(pixbuf);
    g_object_unref(sized);
    //g_print("%d %d\n",width,height);
    return TRUE;
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    //Initalize main window
    GtkBuilder *builder=gtk_builder_new_from_file("res/window.ui");
    GObject *window=gtk_builder_get_object(builder,"window");
    gtk_application_add_window(app,GTK_WINDOW(window));
    gtk_widget_show_all(GTK_WIDGET(window));
    g_signal_connect(window,"window-state-event",G_CALLBACK(window_resize),builder);
}

int main(int argc,char *argv[]){
    //Create and run a application
    GtkApplication *app;
    int status;
    app=gtk_application_new("com.github.daleclack.gtk41",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    return status;
}
