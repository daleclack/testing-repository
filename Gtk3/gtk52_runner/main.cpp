#include <gtk/gtk.h>
#include <thread>

void run_code(GtkWidget *widget,GtkEntry *entry){
	//Get text and run a app
	const char *str;
	str=gtk_entry_get_text(entry);
	std::thread first (system,str);
	first.detach();
}

static void gtkmain(GtkApplication *app,gpointer user_data){
	GtkWidget *window,*vbox,*entry,*btn_run;
	//Create a new window
	window=gtk_application_window_new(app);
	gtk_window_set_default_size(GTK_WINDOW(window),300,100);
	gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
	//Pack Widgets
	vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
	entry=gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry),"cmd");
	g_signal_connect(entry,"activate",G_CALLBACK(run_code),entry);
	gtk_box_pack_start(GTK_BOX(vbox),entry,FALSE,FALSE,0);
	btn_run=gtk_button_new_with_label("Run");
	g_signal_connect(btn_run,"clicked",G_CALLBACK(run_code),entry);
	gtk_box_pack_start(GTK_BOX(vbox),btn_run,FALSE,FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	gtk_widget_show_all(window);
}

int main(int argc,char **argv){
	GtkApplication *app;
	app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
	g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
	return g_application_run(G_APPLICATION(app),argc,argv);
}
