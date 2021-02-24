#include "win1.h"

void win1_init(GtkWidget *widget,GtkWindow *parent){
    GtkBuilder *win1=gtk_builder_new_from_resource("/gtk42/win1.ui");
    GObject *window1=gtk_builder_get_object(win1,"window1");
    gtk_window_set_transient_for(GTK_WINDOW(window1),parent);
    g_signal_connect_swapped(window1,"response",G_CALLBACK(gtk_widget_destroy),window1);
    gtk_widget_show_all(GTK_WIDGET(window1));
}
