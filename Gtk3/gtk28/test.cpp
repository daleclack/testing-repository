#include "test.h"

void print(GtkWidget *widget,gpointer data){
    g_print("hello");
}

void quit(GtkWidget *widget,gpointer data){
    gtk_widget_destroy((GtkWidget *)data);
}
