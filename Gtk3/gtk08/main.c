#include<gtk/gtk.h>
void hello(GtkWidget *widget,gpointer *window){
	GtkWidget *dialog;
	dialog=gtk_message_dialog_new(window,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Hello World");
	gtk_window_set_title(GTK_WINDOW(dialog),"gtk(8)");
	gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
	gtk_button_set_label((GtkButton*)gtk_dialog_get_widget_for_response(GTK_DIALOG(dialog),GTK_RESPONSE_OK),"OK");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}
int main(int argc,char *argv[]){
	gtk_init(&argc,&argv);
	GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *button=gtk_button_new_with_label("Hello");
	gtk_window_set_title(GTK_WINDOW(window),"gtk(8)");
	gtk_window_set_default_size(GTK_WINDOW(window),120,30);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_add(GTK_CONTAINER(window),button);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),(gpointer)window);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hello),NULL);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
