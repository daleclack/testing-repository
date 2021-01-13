#include <gtk/gtk.h>

void check_released(GtkApplication *app,gint index){
    //Check the selection
    switch(index){
        case 1:
        g_print("button1 checked!\n");break;
        case 2:
        g_print("button2 checked!\n");break;
    }
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    //Get window
    GtkBuilder *builder=gtk_builder_new_from_file("window.ui");
    GObject *window=gtk_builder_get_object(builder,"window");
    //Get radiobuttons
    GObject *radio1=gtk_builder_get_object(builder,"radiobutton1");
    GObject *radio2=gtk_builder_get_object(builder,"radiobutton2");
    g_signal_connect(radio1,"released",G_CALLBACK(check_released),(gpointer)1);
    g_signal_connect(radio2,"released",G_CALLBACK(check_released),(gpointer)2);
    //Get "exit" button
    GObject *btnexit=gtk_builder_get_object(builder,"BtnExit");
    g_signal_connect_swapped(btnexit,"clicked",G_CALLBACK(gtk_widget_destroy),window);
    gtk_application_add_window(app,GTK_WINDOW(window));
    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc,char *argv[]){
    //Start the application
    GtkApplication *app;
    app=gtk_application_new("com.github.daleclack.gtk33",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}