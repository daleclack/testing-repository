#include<gtk/gtk.h>
void dialog1(GtkWidget *widget,gpointer data){
	GtkWidget *dialog;
	dialog=gtk_message_dialog_new(GTK_WINDOW(data),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Button Clicked","gtk(9)");
	gtk_window_set_title(GTK_WINDOW(dialog),"gtk(8)");
	gtk_button_set_label((GtkButton*)gtk_dialog_get_widget_for_response(GTK_DIALOG(dialog),GTK_RESPONSE_OK),"OK");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}
int main(int argc,char *argv[]){
	GtkWidget *window;
	GtkWidget *table;
	GtkWidget *button1;
	GtkWidget *button2;
	GtkWidget *button3;
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"gtk(9)");
	gtk_window_set_default_size(GTK_WINDOW(window),180,120);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	table=gtk_table_new(2,2,TRUE);
	gtk_container_add(GTK_CONTAINER(window),table);
	button1=gtk_button_new_with_label("button 1");
	gtk_table_attach_defaults(GTK_TABLE(table),button1,0,1,0,1);
	g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(dialog1),(gpointer)(window));
	button2=gtk_button_new_with_label("button 2");
	gtk_table_attach_defaults(GTK_TABLE(table),button2,1,2,0,1);
	g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(dialog1),(gpointer)(window));
    button3=gtk_button_new_with_label("Exit");
	gtk_table_attach_defaults(GTK_TABLE(table),button3,0,2,1,2);
	g_signal_connect(G_OBJECT(button3),"clicked",G_CALLBACK(gtk_main_quit),NULL);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}

