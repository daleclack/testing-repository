#include "xerel.h"
#include <cstdio>
#include <cstring>
#include "360.xpm"
#include "gtkwin.h"
#include "xerelease.h"

void print(GtkWidget *widget,gpointer data){
    //Get local time
    time_t t;
    t=time(NULL);
    struct tm *local;
    local=localtime(&t);
    const gchar *filename;
    int flag;//flag=0,longterm;flag=1,stable;flag=3,develment
    //Use the combo box id to check the selection
    int id=gtk_combo_box_get_active(GTK_COMBO_BOX(data));
    switch(id){
        case 0:
        filename="config_lts";flag=0;break;
        case 1:
        filename="config_stable";flag=1;break;
        case 2:
        filename="config_devel";flag=2;break;
    }
    char str[57],ver[15];
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp==NULL){
        MsgBox("Error","The config file not exist!\nUse Change config menu for a config");
    }else{
        switch(flag){
        case 0:
            fgets(ver,15,fp);
            longterm(local,ver,str);
            MsgBox("Xe release 9",str);
            break;
        case 1:
            fgets(ver,15,fp);
            stable(local,ver,str);
            MsgBox("Xe release 9",str);
            break;
        case 2:
            fgets(ver,15,fp);
            develop(local,ver,str);
            MsgBox("Xe release 9",str);
        }
    }
    fclose(stdin);
}

void quit(GtkWidget *widget,gpointer data){
    gtk_widget_destroy((GtkWidget *)data);
}

void about_activate(GtkWidget *widget,gpointer data){
    MsgBox("About xerelease9","xerelease9 by daleclack\n2020-2021 Xe Corporation");
}

void config_activate(GtkWidget *widget,gpointer data){
    InputBox("Input xe lts config","config_lts");
}

void config1_activate(GtkWidget *widget,gpointer data){
    InputBox("Input xe stable config","config_stable");
}

void config2_activate(GtkWidget *widget,gpointer data){
    InputBox("Input xe devel config","config_devel");
}

void InputBox(const gchar *content,const char *filename){
    //Initalize InputBox
    const gchar *str;
    int response;
    GtkWidget *dialog=gtk_dialog_new();
    GtkWindow *_dialog=GTK_WINDOW(dialog);
    GtkDialog *dialog1=GTK_DIALOG(dialog);
    gtk_window_set_default_size(_dialog,300,150);
    gtk_window_set_position(_dialog,GTK_WIN_POS_CENTER);
    gtk_window_set_title(_dialog,"Change config");
    gtk_dialog_add_buttons(dialog1,"Cancel",GTK_RESPONSE_CANCEL,"OK",GTK_RESPONSE_OK,NULL);

    //Get content_area and put entry and label to the dialog
    GtkWidget *content_area=gtk_dialog_get_content_area(GTK_DIALOG(_dialog));
    GtkContainer *_content_area=GTK_CONTAINER(content_area);
    GtkWidget *label=gtk_label_new(" ");
    gtk_container_add(_content_area,label);
    label=gtk_label_new(content);
    gtk_container_add(_content_area,label);
    label=gtk_label_new(" ");
    GtkWidget *entry=gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry),"default config");
    g_signal_connect(entry,"activate",G_CALLBACK(entry_activate),(gpointer)dialog);

    gtk_container_add(_content_area,label);
    gtk_container_add(_content_area,entry);
    gtk_widget_show_all(content_area);
    response=gtk_dialog_run(dialog1);
    //Check the response and update the file with the "OK" Response
    if(response==GTK_RESPONSE_OK){
        str=gtk_entry_get_text(GTK_ENTRY(entry));
        if(strlen(str)!=0){
            freopen(filename,"w",stdout);
            g_print(str);
            fclose(stdout);
            gtk_widget_destroy(dialog);
            MsgBox("Change config","Config changed!\nPlease Restart the application");
        }else{
            gtk_widget_destroy(dialog);
        }
    }else{
    gtk_widget_destroy(dialog);
    }
}

void entry_activate(GtkWidget *widget,gpointer data){
    gtk_dialog_response(GTK_DIALOG(data),GTK_RESPONSE_OK);
}

void MsgBox(const gchar *title,const gchar *msg){
    //Initalize the MsgBox
    GtkWidget *dialog=gtk_dialog_new();
    GtkWindow *win=GTK_WINDOW(dialog);
    gtk_window_set_default_size(win,300,150);
    gtk_window_set_position(win,GTK_WIN_POS_CENTER);
    gtk_window_set_title(win,title);
    gtk_dialog_add_button(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK);

    //Get GtkDialog's content_area and put widgets
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

    //Add a GtkBox to the dialog and run
    gtk_container_add(_content_area,hbox.hbox);
    gtk_widget_show_all(content_area);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
