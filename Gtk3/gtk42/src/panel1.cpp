#include <ctime>
#include "panel1.h"
#include "winconf.h"
#include "background.h"

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

void add_toppanel(GtkBuilder *builder,GtkFixed *fixed){
    //Get position
    int width=640,height=480;
    get_config(&width,&height);
    //Get panel
    GtkBuilder *panel=gtk_builder_new_from_resource("/gtk42/toppanel.ui");
    GObject *panel1=gtk_builder_get_object(panel,"btnbox");
    gtk_widget_set_size_request(GTK_WIDGET(panel1),width,15);
    //Get timer label and set time
    GObject *label_time=gtk_builder_get_object(panel,"label_time");
    g_timeout_add(100,change_time,label_time);
    //Get popover window
    GObject *popover=gtk_builder_get_object(panel,"popover1");
    //Get button for change background
    GObject *btn_back=gtk_builder_get_object(panel,"btnback");
    GObject *img_back=gtk_builder_get_object(panel,"image3");
    gtk_image_set_from_resource(GTK_IMAGE(img_back),"/gtk42/graphics.png");
    //gtk_button_set_image(GTK_BUTTON(btn_back),GTK_WIDGET(img_back));
    gtk_button_set_always_show_image(GTK_BUTTON(btn_back),TRUE);
    g_signal_connect(btn_back,"clicked",G_CALLBACK(fileopen),builder);
    g_signal_connect_swapped(btn_back,"clicked",G_CALLBACK(gtk_widget_hide),popover);
    //Config button
    GObject *btn_conf=gtk_builder_get_object(panel,"btnset");
    GObject *img_set=gtk_builder_get_object(panel,"image5");
    gtk_image_set_from_resource(GTK_IMAGE(img_set),"/gtk42/system.png");
    //gtk_button_set_image(GTK_BUTTON(btn_conf),GTK_WIDGET(img_set));
    gtk_button_set_always_show_image(GTK_BUTTON(btn_conf),TRUE);
    g_signal_connect(btn_conf,"clicked",G_CALLBACK(conf_dialog),builder);
    g_signal_connect_swapped(btn_conf,"clicked",G_CALLBACK(gtk_widget_hide),popover);
    //Get Exit button
    GObject *btn_exit=gtk_builder_get_object(panel,"PanelExit");
    GObject *img_exit=gtk_builder_get_object(panel,"image4");
    gtk_image_set_from_resource(GTK_IMAGE(img_exit),"/gtk42/log-out.png");
    //gtk_button_set_image(GTK_BUTTON(btn_exit),GTK_WIDGET(img_exit));
    gtk_button_set_always_show_image(GTK_BUTTON(btn_exit),TRUE);
    GObject *window=gtk_builder_get_object(builder,"window");
    g_signal_connect_swapped(btn_exit,"clicked",G_CALLBACK(gtk_widget_destroy),window);
    gtk_fixed_put(fixed,GTK_WIDGET(panel1),0,0);
}
