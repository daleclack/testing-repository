#include <gtk/gtk.h>
#include <thread>

void run_code(GtkWidget *widget,GtkBuilder *builder){
	GObject *window,*check1,*entry;
	const char *str;
	gboolean flag;
	window=gtk_builder_get_object(builder,"window");
	check1=gtk_builder_get_object(builder,"check1");
	entry=gtk_builder_get_object(builder,"entry");
	str=gtk_entry_get_text(GTK_ENTRY(entry));
	std::thread first (system,str);
	first.detach();
	flag=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check1));
	if(flag==TRUE) gtk_widget_destroy(GTK_WIDGET(window));
}

static void gtkmain(GtkApplication *app,gpointer user_data){
	GtkBuilder *builder=gtk_builder_new_from_resource("/gtk53/window.ui");
	GObject *window,*entry,*btnok,*btncancel;
	window=gtk_builder_get_object(builder,"window");
	gtk_application_add_window(app,GTK_WINDOW(window));
	entry=gtk_builder_get_object(builder,"entry");
	gtk_entry_set_text(GTK_ENTRY(entry),"cmd");
	g_signal_connect(entry,"activate",G_CALLBACK(run_code),builder);
	btnok=gtk_builder_get_object(builder,"btnok");
	g_signal_connect(btnok,"clicked",G_CALLBACK(run_code),builder);
	btncancel=gtk_builder_get_object(builder,"btncancel");
	g_signal_connect_swapped(btncancel,"clicked",G_CALLBACK(gtk_widget_destroy),window);
	gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc,char **argv){
	GtkApplication *app;
	app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
	g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
	return g_application_run(G_APPLICATION(app),argc,argv);
}
