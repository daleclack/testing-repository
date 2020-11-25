#include <gtk/gtk.h>
#include <stdio.h>

void entry_activate(GtkWidget *widget,gpointer data){
    //Deal with activate and click signal
    //This function is for getting text of entry and write text to a file
    const gchar *str;
    str=gtk_entry_get_text(GTK_ENTRY(data));
    freopen("test1.txt","w",stdout);
    g_print("%s\n",str);
    fclose(stdout);
}

void activate(GtkApplication *app,gpointer user_data){
    //Create a window
    GtkWidget *window;
    window=gtk_application_window_new(app);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window),"gtk (20)");
    gtk_window_set_default_size(GTK_WINDOW(window),400,200);
    GtkWidget *fixed=gtk_fixed_new();

    //Create a entry
    GtkWidget *entry=gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry),"hello");
    gtk_widget_set_size_request(entry,300,50);
    gtk_fixed_put(GTK_FIXED(fixed),entry,50,40);
    g_signal_connect(G_OBJECT(entry),"activate",G_CALLBACK(entry_activate),(gpointer)entry);

    //Create a button with label
    GtkWidget *button=gtk_button_new_with_label("Print");
    gtk_widget_set_size_request(button,100,50);
    gtk_fixed_put(GTK_FIXED(fixed),button,75,100);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(entry_activate),(gpointer)entry);

    //Create a Exit button
    GtkWidget *button_exit=gtk_button_new_with_label("Exit");
    gtk_widget_set_size_request(button_exit,100,50);
    gtk_fixed_put(GTK_FIXED(fixed),button_exit,225,100);
    g_signal_connect(G_OBJECT(button_exit),"clicked",G_CALLBACK(gtk_main_quit),NULL);

    //Add everything to window
    gtk_container_add(GTK_CONTAINER(window),fixed);
    gtk_widget_show_all(window);
}

int main(int argc,char *argv[]){
    //Create a gtk application
    GtkApplication *app;
    int status;
    app=gtk_application_new("com.github.daleclack.gtk20",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    return status;
}
