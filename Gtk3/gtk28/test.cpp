#include "test.h"
#include <cstdio>
#include <cstring>
#include "360.xpm"
#include "gtkwin.h"

void print(GtkWidget *widget,gpointer data){
    char str[57];
    freopen("config","r",stdin);
    fgets(str,57,stdin);
    g_print("%s",str);
    fclose(stdin);
}

void quit(GtkWidget *widget,gpointer data){
    gtk_widget_destroy((GtkWidget *)data);
}

void about_activate(GtkWidget *widget,gpointer data){
    MsgBox("gtk28 by daleclack\n2020 Xe Corporation");
}

void config_activate(GtkWidget *widget,gpointer data){
    const gchar *str;
    int response;
    GtkWidget *dialog=gtk_dialog_new();
    GtkWindow *_dialog=GTK_WINDOW(dialog);
    GtkDialog *dialog1=GTK_DIALOG(dialog);
    gtk_window_set_default_size(_dialog,300,150);
    gtk_window_set_position(_dialog,GTK_WIN_POS_CENTER);
    gtk_window_set_title(_dialog,"Change config");
    gtk_dialog_add_buttons(dialog1,"Cancel",GTK_RESPONSE_CANCEL,"OK",GTK_RESPONSE_OK,NULL);

    GtkWidget *content_area=gtk_dialog_get_content_area(GTK_DIALOG(_dialog));
    GtkContainer *_content_area=GTK_CONTAINER(content_area);
    GtkWidget *label=gtk_label_new("Input config");
    GtkWidget *entry=gtk_entry_new();

    gtk_container_add(_content_area,label);
    gtk_container_add(_content_area,entry);
    gtk_widget_show_all(content_area);
    response=gtk_dialog_run(dialog1);
    if(response==GTK_RESPONSE_OK){
        str=gtk_entry_get_text(GTK_ENTRY(entry));
        freopen("config","w",stdout);
        g_print(str);
        fclose(stdout);
        gtk_widget_destroy(dialog);
        MsgBox("Config changed!\nPlease Restart the application");
    }else{
    gtk_widget_destroy(dialog);
    }
}

void MsgBox(const gchar *msg){
    GtkWidget *dialog=gtk_dialog_new();
    GtkWindow *win=GTK_WINDOW(dialog);
    gtk_window_set_default_size(win,300,150);
    gtk_window_set_position(win,GTK_WIN_POS_CENTER);
    gtk_window_set_title(win,"Change config");
    gtk_dialog_add_button(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK);

    GtkWidget *content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkContainer *_content_area=GTK_CONTAINER(content_area);
    GtkWidget *label=gtk_label_new(" ");
    gtk_container_add(_content_area,label);
    HBox hbox;
    label=gtk_label_new("   ");
    Icon msg_icon;
    msg_icon.get_image(_60,50,50);
    hbox.pack_start(label,FALSE,FALSE,5);
    hbox.pack_start(msg_icon.img1,FALSE,FALSE,5);
    label=gtk_label_new(msg);
    hbox.pack_start(label,FALSE,FALSE,5);

    gtk_container_add(_content_area,hbox.hbox);
    gtk_widget_show_all(content_area);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
