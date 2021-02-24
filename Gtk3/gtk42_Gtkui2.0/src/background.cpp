#include "background.h"
#include "winconf.h"
#include "winpe.xpm"

void fileopen(GtkWidget *widget,GtkBuilder *builder){
    GObject *parent=gtk_builder_get_object(builder,"window");
    //Change background
    GtkWidget *dialog;
    GtkFileChooserAction action=GTK_FILE_CHOOSER_ACTION_OPEN;
    dialog=gtk_file_chooser_dialog_new("Choose a image File",GTK_WINDOW(parent),action,
    "OK",GTK_RESPONSE_OK,"Cancel",GTK_RESPONSE_CANCEL,NULL);
    //Use GtkFileFilter to select image file
    GtkFileFilter *filter=gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter,"*.png");
    gtk_file_filter_add_pattern(filter,"*.jpg");
    gtk_file_filter_add_pattern(filter,"*.jpeg");
    gtk_file_filter_add_pattern(filter,"*.bmp");
    gtk_file_filter_add_pattern(filter,"*.xpm");
    gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog),filter);
    gtk_widget_show(dialog);
    g_signal_connect(dialog,"response",G_CALLBACK(dialog_response),builder);
}

void dialog_response(GtkWidget *widget,int response,GtkBuilder *builder){
    //Handle file chooser response and set background
    int width=640,height=360;
    get_config(&width,&height);
    GObject *background=gtk_builder_get_object(builder,"background");
    const gchar *filename;
    GFile *file;
    //g_print("%s\n",filename);
    if(response==GTK_RESPONSE_OK){
        file=gtk_file_chooser_get_file(GTK_FILE_CHOOSER(widget));
        filename=g_file_get_path(file);
        GdkPixbuf *pixbuf=gdk_pixbuf_new_from_file(filename,NULL);
        GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,width,height,GDK_INTERP_BILINEAR);
        gtk_image_set_from_pixbuf(GTK_IMAGE(background),sized);
        g_object_unref(pixbuf);
        g_object_unref(sized);
    }
    gtk_widget_destroy(widget);
}

void default_background(GtkBuilder *builder){
    //Set the default background
    int width=640,height=360;
    get_config(&width,&height);
    GObject *background=gtk_builder_get_object(builder,"background");
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_xpm_data(winpe);
    GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,width,height,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(background),sized);
}
