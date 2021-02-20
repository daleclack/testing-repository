#include "win1.h"

void win1_init(GtkWidget *widget,gpointer data){
    GtkBuilder *win1=gtk_builder_new_from_resource("/gtk42/win1.ui");
    GObject *window1=gtk_builder_get_object(win1,"window1");
    gtk_widget_show_all(GTK_WIDGET(window1));
}
