#include <gtk/gtk.h>
#include <res/winpe.xpm>

GtkWidget *background;
GFile *file;

void set_background(GFile *file1,int width,int height){
    const gchar *filename;
    filename=g_file_get_path(file1);
    //g_print("%s",filename);
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_file(filename,NULL);
    GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,width,height,GDK_INTERP_BILINEAR);
    gtk_picture_set_pixbuf(GTK_PICTURE(background),sized);
    g_object_unref(pixbuf);
    g_object_unref(sized);
}

void dialog_response(GtkWidget *widget,int response){
    //Handle file chooser response and set background
    const gchar *filename;
    //g_print("%s\n",filename);
    if(response==GTK_RESPONSE_OK){
        file=gtk_file_chooser_get_file(GTK_FILE_CHOOSER(widget));
        //gtk_picture_set_file(GTK_PICTURE(background),file);
        //filename=g_file_get_path(file);
        set_background(file,640,360);
    }
    gtk_window_destroy(GTK_WINDOW(widget));
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

void default_background(int width,int height){
    //Image as background
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_xpm_data(winpe);
    GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,width,height,GDK_INTERP_BILINEAR);
    background=gtk_picture_new_for_pixbuf(sized);
    g_object_unref(pixbuf);
    g_object_unref(sized);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*overlay,*button,*header,*draw_area;
    //Window initalize
    window=gtk_application_window_new(app);
    //gtk_window_set_default_size(GTK_WINDOW(window),640,360);
    gtk_window_set_title(GTK_WINDOW(window),"gtk4-test2");
    //Window icon
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    //GtkHeaderBar
    header=gtk_header_bar_new();
    gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(header),TRUE);
    gtk_header_bar_set_decoration_layout(GTK_HEADER_BAR(header),"close,minimize,maximize:icon");
    gtk_window_set_titlebar(GTK_WINDOW(window),header);
    //GtkOverlay:Lay widget on the top of background
    overlay=gtk_overlay_new();
    default_background(640,360);
    gtk_widget_set_size_request(background,640,360);
    gtk_overlay_set_child(GTK_OVERLAY(overlay),background);
    //GtkButton
    button=gtk_button_new_with_label("Change Background");
    //gtk_widget_set_size_request(button,200,50);
    gtk_widget_set_halign(button,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button,GTK_ALIGN_CENTER);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay),button);
    g_signal_connect(button,"clicked",G_CALLBACK(change_background),window);
    //Show all widget
    gtk_window_set_child(GTK_WINDOW(window),overlay);
    gtk_widget_show(window);
}

int main(int argc,char *argv[]){
    int status;
    GtkApplication *app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    return status;
}
