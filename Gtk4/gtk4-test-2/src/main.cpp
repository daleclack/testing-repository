#include <gtk/gtk.h>
#include "res/winpe.xpm"

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*image,*box;
    GdkPixbuf *pixbuf,*sized;
    box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    window=gtk_application_window_new(app);
    pixbuf=gdk_pixbuf_new_from_xpm_data(winpe);
    sized=gdk_pixbuf_scale_simple(pixbuf,480,360,GDK_INTERP_BILINEAR);
    image=gtk_image_new_from_pixbuf(sized);
    gtk_widget_set_size_request(image,400,300);
    gtk_box_append(GTK_BOX(box),image);
    gtk_window_set_child(GTK_WINDOW(window),box);
    gtk_widget_show(window);
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    int status;
    app=gtk_application_new("com.daleclack.gtk4.test2",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    return status;
}
