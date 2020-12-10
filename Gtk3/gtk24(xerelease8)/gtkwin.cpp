#include <stdio.h>
#include "gtkwin.h"
#include "xerelease.h"
#include "winpe.xpm"
#include "img.xpm"
#include "xeapi.h"

void gtkwin_config(GtkWidget *window)
{
    //Config main window
    gtk_window_set_title(GTK_WINDOW(window),"Xe release 8");
    gtk_window_set_default_size(GTK_WINDOW(window),400,300);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

    //Icon config
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_xpm_data(img);
    gtk_window_set_icon(GTK_WINDOW(window),pixbuf);
    g_object_unref(pixbuf);
}

void image_config(GtkImage *image)
{
    GdkPixbuf *pixbuf;
    GdkPixbuf *sized;
    pixbuf=gdk_pixbuf_new_from_xpm_data(winpe);
    sized=gdk_pixbuf_scale_simple(pixbuf,400,300,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(image,sized);
    g_object_unref(pixbuf);
    g_object_unref(sized);
}

void combo_config(GtkWidget *combo)
{
    gtk_widget_set_size_request(combo,100,50);
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),"Xe 5.x");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),"Xe 6.x");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo),0);
}

void button_config(GtkWidget *button)
{
    GdkPixbuf *pixbuf;
    GdkPixbuf *sized;
    GtkWidget *image;
    pixbuf=gdk_pixbuf_new_from_xpm_data(img);
    sized=gdk_pixbuf_scale_simple(pixbuf,40,40,GDK_INTERP_BILINEAR);
    image=gtk_image_new_from_pixbuf(sized);
    gtk_button_set_image((GtkButton*)button,image);
    gtk_button_set_relief((GtkButton*)button,GTK_RELIEF_NONE);
}

void layout_add_label(GtkWidget *label)
{
    char str[57];
    time_t t;
    struct tm *local;
    t=time(NULL);
    local=localtime(&t);
    sprintf(str,"Xe Api Version:%d",xeapi1(local));
    gtk_label_set_text(GTK_LABEL(label),str);
}

void button_click(GtkWidget *widget,GtkWidget *combo)
{
    time_t t;
    struct tm *local;
    t=time(NULL);
    local=localtime(&t);
    const char *str;
    char version[57],branch[57];
    str=gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo));
    if(strcmp("Xe 5.x",str)==0){
        release(local,version);
        MsgBox(widget,version);
    }else{
        InputBox(widget,branch);
        develop(local,branch,version);
        MsgBox(widget,version);
    }
}

void MsgBox(GtkWidget *widget,const gchar *str)
{
    //Create a dialog,change proprites and add a "OK" button
    GtkWidget *dialog=gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog),"Xe release 8");
    gtk_window_set_default_size(GTK_WINDOW(dialog),300,150);
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
    gtk_dialog_add_button(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK);

    //Container to put widgets
    GtkWidget *content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    GtkWidget *label=gtk_label_new("   ");

    //Create a image
    GdkPixbuf *pixbuf;
    GdkPixbuf *sized;
    GtkWidget *image;
    pixbuf=gdk_pixbuf_new_from_xpm_data(img);
    sized=gdk_pixbuf_scale_simple(pixbuf,50,50,GDK_INTERP_BILINEAR);
    image=gtk_image_new_from_pixbuf(sized);

    //Put image and label
    GtkWidget *label1=gtk_label_new(str);
    gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox),label1,FALSE,FALSE,0);
    label=gtk_label_new("  ");

    //Add widgets and show
    gtk_container_add(GTK_CONTAINER(content_area),label);
    gtk_container_add(GTK_CONTAINER(content_area),hbox);
    gtk_widget_show_all(content_area);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void InputBox(GtkWidget *widget,char *str)
{
    //Create a dialog,change proprites and add a "OK" button
    GtkWidget *dialog=gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog),"Xe release 8");
    gtk_window_set_default_size(GTK_WINDOW(dialog),300,150);
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
    gtk_dialog_add_button(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK);

    //Get content_area and add label and entry
    GtkWidget *content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *label=gtk_label_new("Input Xe 6 Version");
    GtkWidget *entry=gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry),"6.0");

    gtk_container_add(GTK_CONTAINER(content_area),label);
    gtk_container_add(GTK_CONTAINER(content_area),entry);
    gtk_widget_show_all(content_area);
    gtk_dialog_run(GTK_DIALOG(dialog));
    const gchar *str1=gtk_entry_get_text(GTK_ENTRY(entry));
    strcpy(str,str1);
    gtk_widget_destroy(dialog);
}
