#include<gtk/gtk.h>
void hello(GtkWidget *widget,gpointer data){
	g_print("hello\n");
}
int main(int argc,char *argv[]){
	GtkWidget *window;
	GtkWidget *button;
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_title(GTK_WINDOW(window),"Gtk(3) Test");
	gtk_window_set_default_size(GTK_WINDOW(window),40,20);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	button=gtk_button_new_with_label("hello");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hello),NULL);
	gtk_container_add(GTK_CONTAINER(window),button);
	gtk_widget_show(window);
	gtk_widget_show(button);
	gtk_main();
}
