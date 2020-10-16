#include<gtk/gtk.h>
void hello(GtkWidget *GtkWidget,gpointer user_data){
	g_print(user_data);
	g_print(" clicked\n");
}
int main(int argc,char *argv[]){
	GtkBuilder *builder = gtk_builder_new();
	GObject *window;
	GObject *label;
	GObject *button1;
	GObject *button2;
	GObject *button3;
	gtk_init(&argc,&argv);
	gtk_builder_add_from_file(builder,"ui.glade",NULL);
	window=gtk_builder_get_object(builder,"window1");
	label=gtk_builder_get_object(builder,"label1");
	button1=gtk_builder_get_object(builder,"button1");
	button2=gtk_builder_get_object(builder,"button2");
	button3=gtk_builder_get_object(builder,"button3");
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(hello),"button1");
	g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(hello),"button2");
	g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(hello),"button1");
	gtk_main();
	return 0;
}
