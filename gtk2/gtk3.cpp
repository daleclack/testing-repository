#include<gtk/gtk.h>
void hello(GtkWidget *widget,gpointer data){
	g_print("hello\n");
}
int main(int argc,char *argv[]){
	GtkWidget *window;//Point to window
	GtkWidget *button;//point to button
	gtk_init(&argc,&argv);//inital 
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);//Create a window
	gtk_window_set_title(GTK_WINDOW(window),"Gtk(3) Test");//Window title
	gtk_window_set_default_size(GTK_WINDOW(window),40,20);//Window size
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);//Window Position
	button=gtk_button_new_with_label("hello");//Create button
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hello),NULL);//Call a function when clicked
	gtk_container_add(GTK_CONTAINER(window),button);//Add button to window
	gtk_widget_show(window);//show window
	gtk_widget_show(button);//show button
	gtk_main();//Main Function
	return FALSE;
}
