#include "MyImage.h"
#include "img7.xpm"

static void gtkmain(GtkApplication * app,gpointer user_data){
    GtkWidget * window, * vbox, * sw, * scale;
    
    //Initalize window
    window = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window),800,450);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");

    //Create Child widgets
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
    sw = gtk_scrolled_window_new();

    //Add the image widget
    GtkWidget * img_view = my_image_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(sw),img_view);
    gtk_widget_set_vexpand(sw,TRUE);
    gtk_box_append(GTK_BOX(vbox),sw);

    //Add a scale
    scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,0.01,10.0,0.1);
    gtk_range_set_value(GTK_RANGE(scale),1.0);
    gtk_box_append(GTK_BOX(vbox),scale);

    //Bind the "value" property
    g_object_bind_property(gtk_range_get_adjustment(GTK_RANGE(scale)),"value",
                                                    img_view,"scale",
                                                    G_BINDING_BIDIRECTIONAL);

    //Default Image
    GdkPixbuf * pixbuf = gdk_pixbuf_new_from_xpm_data(img7);
    my_image_set_pixbuf(MY_IMAGE(img_view),pixbuf);
    g_object_unref(pixbuf);

    gtk_window_set_child(GTK_WINDOW(window),vbox);
    gtk_widget_show(window);
}

int main(int argc,char ** argv){
    //Create a application and start
    GtkApplication * app;
    app = gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}