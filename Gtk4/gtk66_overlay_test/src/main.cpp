#include<gtk/gtk.h>

static void button_clicked(GtkWidget *widget,GtkApplication *app){
    //A text function of gtk_overlay_get_child
    GtkWindow *win=gtk_application_get_active_window(app);
    GtkWidget *overlay,*label;
    overlay=gtk_window_get_child(win);
    label=gtk_overlay_get_child(GTK_OVERLAY(overlay));
    gtk_label_set_label(GTK_LABEL(label),"Test");
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*label1,*label2,*overlay,*button;
    //Main window
    window=gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window),400,100);
    gtk_window_set_icon_name(GTK_WINDOW(window),"gtk66");
    //Overlay widgets
    overlay=gtk_overlay_new();
    //Button
    button=gtk_button_new_with_label("Test");
    g_signal_connect(button,"clicked",G_CALLBACK(button_clicked),app);
    gtk_widget_set_halign(button,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button,GTK_ALIGN_END);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay),button);
    //Label1
    label1=gtk_label_new("label1");
    gtk_widget_set_valign(label1,GTK_ALIGN_START);
    gtk_widget_set_halign(label1,GTK_ALIGN_CENTER);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay),label1);
    //label2
    label2=gtk_label_new("label2");
    gtk_overlay_set_child(GTK_OVERLAY(overlay),label2);
    gtk_window_set_child(GTK_WINDOW(window),overlay);
    gtk_widget_show(window);
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}