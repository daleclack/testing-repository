#include<gtk/gtk.h>
int main(int argc,char *argv[]){
	GtkWidget *window;
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"quit_event",G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_title(GTK_WINDOW(window),"gtk(2) test");
	gtk_window_set_default_size(GTK_WINDOW(window),400,300);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_widget_show(window);
	gtk_main();
	return FALSE;
	
}
