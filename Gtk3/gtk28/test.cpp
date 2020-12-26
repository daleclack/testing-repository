#include "test.h"
#include <cstdio>
#include <cstring>
#include "360.xpm"
#include "gtkwin.h"

void print(GtkWidget *widget,gpointer data){
    const gchar *filename;
    int id=gtk_combo_box_get_active(GTK_COMBO_BOX(data));
    switch(id){
        case 0:
        filename="config";break;
        case 1:
        filename="config_1";break;
        case 2:
        filename="config_2";break;
    }
    char str[57];
    freopen(filename,"r",stdin);
    fgets(str,57,stdin);
    MsgBox("Test",str);
    fclose(stdin);
}

void quit(GtkWidget *widget,gpointer data){
    gtk_widget_destroy((GtkWidget *)data);
}

void about_activate(GtkWidget *widget,gpointer data){
    MsgBox("About gtk(28)","gtk28 by daleclack\n2020 Xe Corporation");
}

void config_activate(GtkWidget *widget,gpointer data){
    InputBox("Input config","config");
}

void config1_activate(GtkWidget *widget,gpointer data){
    InputBox("Input config1","config_1");
}

void config2_activate(GtkWidget *widget,gpointer data){
    InputBox("Input config2","config_2");
}

void InputBox(const gchar *content,const char *filename){
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
    GtkWidget *label=gtk_label_new(" ");
    gtk_container_add(_content_area,label);
    label=gtk_label_new(content);
    gtk_container_add(_content_area,label);
    label=gtk_label_new(" ");
    GtkWidget *entry=gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry),"default config");

    gtk_container_add(_content_area,label);
    gtk_container_add(_content_area,entry);
    gtk_widget_show_all(content_area);
    response=gtk_dialog_run(dialog1);
    if(response==GTK_RESPONSE_OK){
        str=gtk_entry_get_text(GTK_ENTRY(entry));
        freopen(filename,"w",stdout);
        g_print(str);
        fclose(stdout);
        gtk_widget_destroy(dialog);
        MsgBox("Change config","Config changed!\nPlease Restart the application");
    }else{
    gtk_widget_destroy(dialog);
    }
}

void MsgBox(const gchar *title,const gchar *msg){
    GtkWidget *dialog=gtk_dialog_new();
    GtkWindow *win=GTK_WINDOW(dialog);
    gtk_window_set_default_size(win,300,150);
    gtk_window_set_position(win,GTK_WIN_POS_CENTER);
    gtk_window_set_title(win,title);
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
