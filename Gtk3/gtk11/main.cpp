#include<gtk/gtk.h>
void hello(GtkWidget *widget,gpointer data){
	g_print("%s ",(gchar*)data);
}
int main(int argc,char **argv){
	GtkWidget *window;
	GtkWidget *button;
	char str1[20]="hello";
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    button=gtk_button_new_with_label("print");
    gtk_container_add(GTK_CONTAINER(window),button);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hello),(gpointer)str1);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
