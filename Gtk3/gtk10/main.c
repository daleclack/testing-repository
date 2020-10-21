#include<gtk/gtk.h>
int main(int argc,char *argv){
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *button1;
	GtkWidget *button2;
	GtkWidget *button3;
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"gtk(10)");
	gtk_window_set_default_size(GTK_WINDOW(window),300,150);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    grid=gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window),grid);
    button1=gtk_button_new_with_label("button 1");
    gtk_grid_attach(GTK_GRID(grid),button1,0,0,1,1);
    button2=gtk_button_new_with_label("button 2");
    gtk_grid_attach(GTK_GRID(grid),button2,1,0,1,1);
    button3=gtk_button_new_with_label("button 3");
    gtk_grid_attach(GTK_GRID(grid),button3,0,1,2,1);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
