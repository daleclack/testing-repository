#include<gtk/gtk.h>
#include"img.xpm"
#include"xeapi.h"
#include<stdio.h>

void MsgBox(GtkWidget *widget,gpointer data){
    GtkWidget *dialog;
    GtkWidget *label;
    GtkWidget *label1;
    GtkWidget *content_area;
    GtkWidget *hbox;
    GdkPixbuf *pixmap;
    GdkPixbuf *image;
    GtkWidget *image1;
    const char *str;
    char str1[57];
    time_t t;
    struct tm *local;
    t=time(NULL);
    local=localtime(&t);
    dialog=gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog),"Xe-api");
    gtk_window_set_default_size(GTK_WINDOW(dialog),300,150);
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
    gtk_dialog_add_button(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK);
    str=gtk_entry_get_text(GTK_ENTRY(data));
    sprintf(str1,"Xe %s Api Version:%d",str,xeapi1(local));
    pixmap=gdk_pixbuf_new_from_xpm_data(img);
    image=gdk_pixbuf_scale_simple(pixmap,40,40,GDK_INTERP_BILINEAR);
    image1=gtk_image_new_from_pixbuf(image);
    content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);
    label1=gtk_label_new(" ");
    gtk_widget_set_size_request(label1,300,30);
    gtk_container_add(GTK_CONTAINER(content_area),label1);
    gtk_container_add(GTK_CONTAINER(content_area),hbox);
    label1=gtk_label_new("    ");
    label=gtk_label_new(str1);
    gtk_box_pack_start(GTK_BOX(hbox),label1,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox),image1,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);
    gtk_widget_show_all(content_area);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    g_object_unref(pixmap);
    g_object_unref(image);
}

static void activate(GtkApplication *app,gpointer user_data){
    GtkWidget *window;
    GtkWidget *fixed;
    GtkWidget *button;
    GdkPixbuf *pixmap;
    GdkPixbuf *image;
    GtkWidget *image1;
    GtkWidget *entry;
    GtkWidget *label;
    window=gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"gtk (17)");
    gtk_window_set_default_size(GTK_WINDOW(window),300,200);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed=gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    button=gtk_button_new();
    gtk_widget_set_size_request(button,50,50);
    pixmap=gdk_pixbuf_new_from_xpm_data(img);
    image=gdk_pixbuf_scale_simple(pixmap,40,40,GDK_INTERP_BILINEAR);
    image1=gtk_image_new_from_pixbuf(image);
    gtk_button_set_image(GTK_BUTTON(button),image1);
    gtk_button_set_relief(GTK_BUTTON(button),GTK_RELIEF_NONE);
    gtk_fixed_put(GTK_FIXED(fixed),button,125,120);
    entry=gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry),"6.0");
    gtk_widget_set_size_request(entry,200,40);
    gtk_fixed_put(GTK_FIXED(fixed),entry,50,70);
    label=gtk_label_new("Input Xeinit version");
    gtk_widget_set_size_request(label,160,40);
    gtk_fixed_put(GTK_FIXED(fixed),label,70,30);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(MsgBox),(gpointer)entry);
    g_signal_connect(G_OBJECT(entry),"activate",G_CALLBACK(MsgBox),(gpointer)entry);
    gtk_widget_show_all(window);
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    int app_status;
    app=gtk_application_new("org.daleclack.gtk17",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
    app_status=g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    return app_status;
}
