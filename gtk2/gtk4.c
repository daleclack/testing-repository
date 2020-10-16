#include<gtk/gtk.h>
void hello(GtkWidget *widget,gpointer data){
	g_print("%s",(gchar*)data);
}
int main(int argc,char *argv[]){
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *box1;
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_title(GTK_WINDOW(window),"gtk(4) Test");
	gtk_window_set_default_size(GTK_WINDOW(window),90,20);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	box1=gtk_hbox_new(FALSE,1);
	gtk_container_add(GTK_CONTAINER(window),box1);
	button=gtk_button_new_with_label("Hello");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hello),"Hello");
	gtk_box_pack_start(GTK_BOX(box1),button,TRUE,TRUE,0);	
	gtk_widget_show(button);
	button=gtk_button_new_with_label("World");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hello),"World");
    gtk_box_pack_start(GTK_BOX(box1),button,TRUE,TRUE,0);
    gtk_widget_show(button);
    button=gtk_button_new_with_label("!");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hello),"!");
    gtk_box_pack_start(GTK_BOX(box1),button,TRUE,TRUE,0);
    gtk_widget_show(button);
    gtk_widget_show(box1);
    gtk_widget_show(window);
    gtk_main();
	return 0;
}
