#include <gtk/gtk.h>
#include <ctime>

gboolean change_time(gpointer data){
    //Get local time
    time_t t;
    struct tm *local;
    t=time(NULL);
    local=localtime(&t);
    //Format the time and set the time
    char current_time[20];
    sprintf(current_time,"%02d:%02d %04d/%02d/%02d",
    local->tm_hour,local->tm_min,local->tm_year+1900,local->tm_mon+1,local->tm_mday);
    //g_print("%s\n",current_time);
    gtk_label_set_label(GTK_LABEL(data),current_time);
    return TRUE;
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    //Create a window
    GtkWidget *window,*vbox,*label_time,*btn_exit;
    window=gtk_application_window_new(app);
    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
    label_time=gtk_label_new("20:00 2021/2/14");
    gtk_box_pack_start(GTK_BOX(vbox),label_time,FALSE,FALSE,0);
    //"Exit" button
    btn_exit=gtk_button_new_with_label("Exit");
    g_signal_connect_swapped(btn_exit,"clicked",G_CALLBACK(gtk_widget_destroy),window);
    gtk_box_pack_start(GTK_BOX(vbox),btn_exit,FALSE,FALSE,0);
    //Set the time
    g_timeout_add(100,change_time,label_time);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    gtk_widget_show_all(window);
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    int status;
    app=gtk_application_new("com.github.daleclack.gtktimer",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    return status;
}
