#include <cstdio>
#include "winconf.h"

void conf_dialog(GtkWidget *widget,GtkWindow *win){
    //Window config dialog
    GtkBuilder *conf_size=gtk_builder_new_from_resource("/gtk69/winsize.ui");
    GObject *dialog=gtk_builder_get_object(conf_size,"dialog");
    gtk_window_set_transient_for(GTK_WINDOW(dialog),win);
    gtk_window_set_icon_name((GtkWindow*)dialog,"gtk69");
    gtk_window_set_title((GtkWindow*)dialog,"Size Config");
    g_signal_connect(dialog,"response",G_CALLBACK(conf_response),conf_size);
    //Set default config
    GtkWidget *btn_width,*btn_height;
    btn_width=(GtkWidget*)gtk_builder_get_object(conf_size,"btn_width");
    gtk_spin_button_set_value((GtkSpinButton*)btn_width,640.0);
    btn_height=(GtkWidget*)gtk_builder_get_object(conf_size,"btn_height");
    gtk_spin_button_set_value((GtkSpinButton*)btn_height,360.0);
    //Get window size
    GObject *btnGet=gtk_builder_get_object(conf_size,"btnGet");
    g_signal_connect(btnGet,"clicked",G_CALLBACK(get_winsize),conf_size);
    //Reset to default
    GObject *btn_default=gtk_builder_get_object(conf_size,"btn_default");
    g_signal_connect(btn_default,"clicked",G_CALLBACK(set_default),conf_size);
    gtk_widget_show_all(GTK_WIDGET(dialog));
}

void conf_response(GtkWidget *widget,int response,GtkBuilder *builder_conf){
    //Get width and height config and put the numbers into winsize.conf file
    GtkWidget *btn_width,*btn_height;
    btn_width=(GtkWidget*)gtk_builder_get_object(builder_conf,"btn_width");
    btn_height=(GtkWidget*)gtk_builder_get_object(builder_conf,"btn_height");
    if(response==GTK_RESPONSE_OK){
        int width,height;
        width=gtk_spin_button_get_value_as_int((GtkSpinButton*)btn_width);
        height=gtk_spin_button_get_value_as_int((GtkSpinButton*)btn_height);
        freopen("winsize.conf","w",stdout);
        g_print("%d %d",width,height);
        fclose(stdout);
    }
    gtk_widget_destroy(widget);
}

void set_default(GtkWidget *widget,GtkBuilder *builder_conf){
    //Discard changes and set to default config
    GtkWidget *btn_width,*btn_height;
    btn_width=(GtkWidget*)gtk_builder_get_object(builder_conf,"btn_width");
    gtk_spin_button_set_value((GtkSpinButton*)btn_width,640.0);
    btn_height=(GtkWidget*)gtk_builder_get_object(builder_conf,"btn_height");
    gtk_spin_button_set_value((GtkSpinButton*)btn_height,360.0);
}

void get_winsize(GtkWidget *widget,GtkBuilder *builder_conf){
    //Get current window size
    int width=640,height=360;
    GtkWindow *window;
    //Get dialog window and entry
    GObject *dialog=gtk_builder_get_object(builder_conf,"dialog");
    GtkWidget *btn_width,*btn_height;
    btn_width=(GtkWidget*)gtk_builder_get_object(builder_conf,"btn_width");
    btn_height=(GtkWidget*)gtk_builder_get_object(builder_conf,"btn_height");
    //Get main window
    window=gtk_window_get_transient_for(GTK_WINDOW(dialog));
    gtk_window_get_size(GTK_WINDOW(window),&width,&height);
    //g_print("%d %d\n",width,height);
    gtk_spin_button_set_value((GtkSpinButton*)btn_width,width);
    gtk_spin_button_set_value((GtkSpinButton*)btn_height,height);
}

void get_config(int *width,int *height){
    freopen("winsize.conf","r",stdin);
    scanf("%d",width);
    scanf("%d",height);
    fclose(stdin);
}
