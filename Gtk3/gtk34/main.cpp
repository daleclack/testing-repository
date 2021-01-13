#include <gtk/gtk.h>

void print(GtkWidget *widget,GtkBuilder *builder){
    gboolean ischecked;
    //Get checkbuttons
    GObject *check[4];
    for(int i=1;i<4;i++){
        char name[57];
        sprintf(name,"check%d",i);
        check[i]=
        gtk_builder_get_object(builder,name);
    }
    //Check and print
    for(int i=1;i<4;i++){
        ischecked=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check[i]));
        if(ischecked==TRUE){
            g_print("%d\n",i);
        }
    }
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    //Get the window from a ui file
    GtkBuilder *builder=gtk_builder_new_from_file("window.ui");
    GObject *window=gtk_builder_get_object(builder,"window");
    //Get "OK" button
    GObject *button=gtk_builder_get_object(builder,"btn_ok");
    g_signal_connect(button,"clicked",G_CALLBACK(print),builder);
    gtk_application_add_window(app,GTK_WINDOW(window));
    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    app=gtk_application_new("com.github.daleclack.gtk34",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}