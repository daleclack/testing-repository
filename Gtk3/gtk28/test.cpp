#include "test.h"
#include <stdio.h>

void print(GtkWidget *widget,gpointer data){
    char str[57];
    FILE *config=NULL;
    config=fopen("config","r");
    fgets(str,57,config);
    g_print("%s",str);
    fclose(stdin);
}

void quit(GtkWidget *widget,gpointer data){
    gtk_widget_destroy((GtkWidget *)data);
}

void config_activate(GtkWidget *widget,gpointer data){
    const gchar *str;
    GtkWidget *dialog=gtk_dialog_new();
    GtkWindow *_dialog=GTK_WINDOW(dialog);
    GtkDialog *dialog1=GTK_DIALOG(dialog);
    gtk_window_set_default_size(_dialog,300,150);
    gtk_window_set_position(_dialog,GTK_WIN_POS_CENTER);
    gtk_window_set_title(_dialog,"Change config");
    gtk_dialog_add_button(dialog1,"OK",GTK_RESPONSE_OK);

    GtkWidget *content_area=gtk_dialog_get_content_area(GTK_DIALOG(_dialog));
    GtkContainer *_content_area=GTK_CONTAINER(content_area);
    GtkWidget *label=gtk_label_new("Input config");
    GtkWidget *entry=gtk_entry_new();

    gtk_container_add(_content_area,label);
    gtk_container_add(_content_area,entry);
    gtk_widget_show_all(content_area);
    gtk_dialog_run(dialog1);
    str=gtk_entry_get_text(GTK_ENTRY(entry));
    freopen("config","w",stdout);
    g_print(str);
    fclose(stdout);
    gtk_widget_destroy(dialog);
}
