#include <gtk/gtk.h>

static void btnstate_clicked(GtkWidget * widget,gpointer data){
    GdkSurface * surface = gtk_native_get_surface(GTK_NATIVE(data));
    GdkToplevelState state = gdk_toplevel_get_state(GDK_TOPLEVEL(surface));
    g_print("%d",state);
}

static void gtkmain(GtkApplication * app,gpointer user_data){
    GtkWidget * window, * vbox, * label_state, * btn_state;
    //Initalize Window
    window = gtk_application_window_new(app);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(window),300,200);

    GtkWidget * win = gtk_window_new();
    
    //Add Widgets
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
    gtk_widget_set_halign(vbox,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vbox,GTK_ALIGN_CENTER);
    label_state = gtk_label_new("");
    gtk_box_append(GTK_BOX(vbox),label_state);
    btn_state = gtk_button_new_with_label("Get Window State");
    g_signal_connect(btn_state,"clicked",G_CALLBACK(btnstate_clicked),win);
    gtk_box_append(GTK_BOX(vbox),btn_state);

    gtk_window_set_child(GTK_WINDOW(window),vbox);
    gtk_widget_show(window);
    gtk_widget_show(win);
}

int main(int argc,char **argv){
    GtkApplication * app;
    app = gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}