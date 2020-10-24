#include<gtk/gtk.h>
void hello(GtkWidget *widget,gpointer data){
	GtkWidget *dialog=gtk_message_dialog_new(GTK_WINDOW(data),
	    GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_INFO,
		GTK_BUTTONS_OK,"hello");
	gtk_window_set_title(GTK_WINDOW(dialog),"gtk(12)");
	gtk_window_set_default_size(GTK_WINDOW(dialog),70,40);
	gtk_button_set_label((GtkButton*)gtk_dialog_get_widget_for_response(GTK_DIALOG(dialog),GTK_RESPONSE_OK),"OK");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}
int main(int argc,char **argv){
	GtkWidget *window;
	GtkWidget *fixed;
	GtkWidget *button;
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"gtk(12)");
	gtk_window_set_default_size(GTK_WINDOW(window),200,150);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    fixed=gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    button=gtk_button_new_with_label("hello");
    gtk_fixed_put(GTK_FIXED(fixed),button,65,60);
    gtk_widget_set_size_request(button,70,20);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hello),(gpointer)window);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
