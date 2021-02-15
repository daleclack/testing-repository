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
    gtk_fixed_put(fixed,GTK_WIDGET(panel),0,25);
    g_object_unref(pixbuf);
    g_object_unref(sized);
}
