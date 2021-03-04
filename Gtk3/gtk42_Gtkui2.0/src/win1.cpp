#include "win1.h"

void win1_init(GtkWidget *widget,GtkWindow *parent){
    //"About" window
    GtkBuilder *win1=gtk_builder_new_from_resource("/gtk42/win1.ui");
    GObject *window1=gtk_builder_get_object(win1,"window1");
    gtk_window_set_transient_for(GTK_WINDOW(window1),parent);
    //Window icon fix for win32 platform
    GdkPixbuf *logo=gdk_pixbuf_new_from_resource("/gtk42/icon.jpg",NULL);
    GdkPixbuf *logo_sized=gdk_pixbuf_scale_simple(logo,100,100,GDK_INTERP_BILINEAR);
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(window1),logo_sized);
    g_signal_connect_swapped(window1,"response",G_CALLBACK(gtk_widget_destroy),window1);
    gtk_widget_show_all(GTK_WIDGET(window1));
}
