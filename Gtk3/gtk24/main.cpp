#include <gtk/gtk.h>
#include "gtkwin.h"

static void activate(GtkApplication *app,gpointer user_data)
{
    //Create a gtk window and some widgets
    GtkWidget *window;
    window=gtk_application_window_new(app);
    GtkWidget *layout=gtk_layout_new(NULL,NULL);
    GtkWidget *background=gtk_image_new();
    GtkWidget *combo=gtk_combo_box_text_new();
    GtkWidget *button=gtk_button_new();
    GtkWidget *label=gtk_label_new("");

    //Set widgets config(window,combo box)
    gtkwin_config(window);
    image_config(GTK_IMAGE(background));
    combo_config(combo);
    button_config(button);
    layout_add_label(label);

    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(button_click),combo);
    //Put widgets
    gtk_layout_put(GTK_LAYOUT(layout),background,0,0);
    gtk_layout_put(GTK_LAYOUT(layout),label,150,50);
    gtk_layout_put(GTK_LAYOUT(layout),combo,150,125);
    gtk_layout_put(GTK_LAYOUT(layout),button,180,200);

    //add widgets and show everything
    gtk_container_add(GTK_CONTAINER(window),layout);
    gtk_widget_show_all(window);
}

int main(int argc,char *argv[])
{
    //Create a new application
    GtkApplication *app;
    int status;
    app=gtk_application_new("com.github.daleclack.gtk24",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    return status;
}
