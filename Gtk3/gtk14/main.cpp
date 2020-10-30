#include<gtk/gtk.h>
void hello(GtkWidget *widget,gpointer data){
	GtkWidget *dialog;
	GtkWidget *content_area;
	GtkWidget *label;
	const gchar *txt;
	txt=gtk_entry_get_text(GTK_ENTRY(data));//Get text
    dialog=gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(dialog),"gtk(14)");
	gtk_window_set_default_size(GTK_WINDOW(dialog),200,90);
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
    gtk_dialog_add_button(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK);
    content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    label=gtk_label_new(txt);
    g_signal_connect_swapped(dialog,"response",G_CALLBACK(gtk_widget_destroy),dialog);
    gtk_container_add(GTK_CONTAINER(content_area),label);
	gtk_widget_show_all(dialog);
}
int main(int argc,char *argv[]){
	GtkWidget *window;
	GtkWidget *fixed;
	GtkWidget *button;
	GtkWidget *entry;
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);//Create a new window
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);//Make sure the application exit normally
    gtk_window_set_title(GTK_WINDOW(window),"gtk(14)");//Title of the window
    gtk_window_set_default_size(GTK_WINDOW(window),150,80);//Size of the window
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);//Position of the window
    fixed=gtk_fixed_new();//Greate a gtk_fixed to place widgets
    gtk_container_add(GTK_CONTAINER(window),fixed);//Add it to the window
    entry=gtk_entry_new();//Create a text entry
    gtk_fixed_put(GTK_FIXED(fixed),entry,0,15);//Put the text entry at fixed position
    button=gtk_button_new_with_label("hello");//A new button
    gtk_widget_set_size_request(button,70,20);//Size of the button
    gtk_fixed_put(GTK_FIXED(fixed),button,40,50);//Add the button at the fixed place
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hello),(gpointer)entry);//Make resoonse when click the button
   	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
