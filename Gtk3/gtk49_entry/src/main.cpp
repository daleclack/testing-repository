#include <gtk/gtk.h>

static void btnvisible_clicked(GtkWidget *widget,gpointer data){
    gtk_entry_set_visibility(GTK_ENTRY(data),gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)));
}

static void btnedit_clicked(GtkWidget *widget,gpointer data){
    gtk_editable_set_editable(GTK_EDITABLE(data),gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)));
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    //Get window
    GtkBuilder *builder=gtk_builder_new_from_file("res/window.ui");
    GObject *window,*btn_edit,*btn_visible,*btn_exit,*entry;
    window=gtk_builder_get_object(builder,"window");
    //Get entry and buttons
    entry=gtk_builder_get_object(builder,"entry");
    btn_edit=gtk_builder_get_object(builder,"btnedit");
    g_signal_connect(btn_edit,"clicked",G_CALLBACK(btnedit_clicked),entry);
    btn_visible=gtk_builder_get_object(builder,"btnvisible");
    g_signal_connect(btn_visible,"clicked",G_CALLBACK(btnvisible_clicked),entry);
    btn_exit=gtk_builder_get_object(builder,"btnExit");
    g_signal_connect_swapped(btn_exit,"clicked",G_CALLBACK(gtk_widget_destroy),window);
    gtk_application_add_window(app,GTK_WINDOW(window));
    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
