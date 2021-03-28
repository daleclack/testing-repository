#include <gtk/gtk.h>

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*vbox;
    GtkBuilder *builder=gtk_builder_new_from_file("app-menu.ui");
    window=gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window),500,200);
    gtk_window_set_title(GTK_WINDOW(window),"Gtk55 MenuTest");
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    GObject *app_menu=gtk_builder_get_object(builder,"app-menu");
    //GtkBuilder *builder1=gtk_builder_new_from_file("menu-bar.ui");
    //GObject *app_menu1=gtk_builder_get_object(builder,"app-menu");
    //menubar=gtk_popover_menu_bar_new_from_model((GMenuModel*)app_menu);
    //menubtn=gtk_menu_button_new();
    //gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(menubtn),G_MENU_MODEL(app_menu));
    gtk_application_set_menubar(app,G_MENU_MODEL(app_menu));
    //gtk_box_append(GTK_BOX(vbox),menubar);
    gtk_window_set_child(GTK_WINDOW(window),vbox);
    gtk_widget_show(window);
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}