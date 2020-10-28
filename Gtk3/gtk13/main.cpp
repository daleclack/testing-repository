#include<gtk/gtk.h>
void hello(GtkWidget *widget,gpointer data){
	GtkWidget *dialog;
	GtkWidget *content_area;
	GtkWidget *label;
	dialog=gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(dialog),"gtk13");
	gtk_window_set_default_size(GTK_WINDOW(dialog),200,90);
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
    gtk_dialog_add_button(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK);
    content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    label=gtk_label_new("Hello");
    g_signal_connect_swapped(dialog,"response",G_CALLBACK(gtk_widget_destroy),dialog);
    gtk_container_add(GTK_CONTAINER(content_area),label);
	gtk_widget_show_all(dialog);
}
int main(int argc,char **argv){
	GtkWidget *window;
	GtkWidget *fixed;
	GtkWidget *button;
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(window),"gtk(13)");
    gtk_window_set_default_size(GTK_WINDOW(window),150,80);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed=gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    button=gtk_button_new_with_label("hello");
    gtk_widget_set_size_request(button,70,20);
    gtk_fixed_put(GTK_FIXED(fixed),button,40,20);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hello),(gpointer)window);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
