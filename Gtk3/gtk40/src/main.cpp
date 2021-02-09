#include <gtk/gtk.h>
#include <res/winpe.xpm>

GtkWidget *background;

void dialog_response(GtkWidget *widget,int response){
    //Handle file chooser response and set background
    const gchar *filename;
    GFile *file;
    //g_print("%s\n",filename);
    if(response==GTK_RESPONSE_OK){
        file=gtk_file_chooser_get_file(GTK_FILE_CHOOSER(widget));
        filename=g_file_get_path(file);
        GdkPixbuf *pixbuf=gdk_pixbuf_new_from_file(filename,NULL);
        GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,540,360,GDK_INTERP_BILINEAR);
        gtk_image_set_from_pixbuf(GTK_IMAGE(background),sized);
    }
    gtk_widget_destroy(widget);
}

void change_background(GtkWidget *widget,GtkWindow *parent){
    //Change background
    GtkWidget *dialog;
    GtkFileChooserAction action=GTK_FILE_CHOOSER_ACTION_OPEN;
    dialog=gtk_file_chooser_dialog_new("Choose a image File",parent,action,
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
    g_signal_connect(dialog,"response",G_CALLBACK(dialog_response),NULL);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*fixed,*button;
    //Window initalize
    window=gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window),540,360);
    gtk_window_set_title(GTK_WINDOW(window),"gtk40(based on Gtk4 test)");
    //Window icon
    gtk_window_set_icon_name(GTK_WINDOW(window),"gtk4-icon");
    //GtkFixed
    fixed=gtk_fixed_new();
    //Image as background
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_xpm_data(winpe);
    GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,540,360,GDK_INTERP_BILINEAR);
    background=gtk_image_new_from_pixbuf(sized);
    gtk_widget_set_size_request(background,480,360);
    gtk_fixed_put(GTK_FIXED(fixed),background,0,0);
    //GtkButton
    button=gtk_button_new_with_label("Change Background");
    gtk_widget_set_size_request(button,200,50);
    gtk_fixed_put(GTK_FIXED(fixed),button,170,240);
    g_signal_connect(button,"clicked",G_CALLBACK(change_background),window);
    //Show all widget
    gtk_container_add(GTK_CONTAINER(window),fixed);
    gtk_widget_show_all(window);
}

int main(int argc,char *argv[]){
    int status;
    GtkApplication *app=gtk_application_new("com.daleclack.gtk4.test",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    return status;
}
