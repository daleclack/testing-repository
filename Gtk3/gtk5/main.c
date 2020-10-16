#include <stdio.h>
#include <stdlib.h>
#include<gtk/gtk.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *button;
	GtkWidget *image;
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_POPUP);
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_title(GTK_WINDOW(window),"gtk(5)");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window),400,300);
	vbox=gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	image=gtk_image_new_from_file("a.png");
	gtk_box_pack_start(GTK_BOX(vbox),image,FALSE,FALSE,0);
	button=gtk_button_new_with_label("Exit");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(gtk_main_quit),NULL);
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,0);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
