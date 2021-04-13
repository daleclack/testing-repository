#include <gtk/gtk.h>

static void win1(GtkWidget *widget,GtkWindow *parent){
    //A child window
    GtkBuilder *builder1=gtk_builder_new_from_resource("/gtk67/win1.ui");
    GtkWidget *win1,*exit,*btnstart,*btnstop,*spinner;
    win1=(GtkWidget*)gtk_builder_get_object(builder1,"win1");
    gtk_window_set_icon_name((GtkWindow*)win1,"gtk67");
    gtk_window_set_title((GtkWindow*)win1,"Gtk Spinner");
    gtk_window_set_transient_for((GtkWindow*)win1,parent);
    //"Exit" button
    exit=(GtkWidget*)gtk_builder_get_object(builder1,"win1exit");
    g_signal_connect_swapped(exit,"clicked",G_CALLBACK(gtk_widget_destroy),win1);
    //Button to control spinner
    btnstart=(GtkWidget*)gtk_builder_get_object(builder1,"btnstart");
    btnstop=(GtkWidget*)gtk_builder_get_object(builder1,"btnstop");
    spinner=(GtkWidget*)gtk_builder_get_object(builder1,"spinner");
    gtk_spinner_start((GtkSpinner*)spinner);
    g_signal_connect_swapped(btnstart,"clicked",G_CALLBACK(gtk_spinner_start),spinner);
    g_signal_connect_swapped(btnstop,"clicked",G_CALLBACK(gtk_spinner_stop),spinner);
    gtk_widget_show_all(win1);
    g_object_unref(builder1);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkBuilder *builder=gtk_builder_new_from_resource("/gtk67/gtkmain.ui");
    GtkWidget *window,*btnwin1,*btnexit;
    //Main window
    window=(GtkWidget*)gtk_builder_get_object(builder,"window");
    gtk_application_add_window(app,(GtkWindow*)window);
    gtk_window_set_icon_name((GtkWindow*)window,"gtk67");
    gtk_window_set_title((GtkWindow*)window,"gtk(67)");
    //"Exit" and "Win1" button
    btnexit=(GtkWidget*)gtk_builder_get_object(builder,"btnexit");
    g_signal_connect_swapped(btnexit,"clicked",G_CALLBACK(gtk_widget_destroy),window);
    btnwin1=(GtkWidget*)gtk_builder_get_object(builder,"btnwin1");
    g_signal_connect(btnwin1,"clicked",G_CALLBACK(win1),window);
    gtk_widget_show_all(window);
    g_object_unref(builder);
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run((GApplication*)app,argc,argv);
}
