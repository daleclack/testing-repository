#include<gtk/gtk.h>
void window1(int argc,char *argv[]){
	gtk_init(&argc,&argv);
    GtkWidget *window;
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(window),"gtk(7)");
    gtk_window_set_default_size(GTK_WINDOW(window),200,50);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_widget_show(window);
    gtk_main();
}
