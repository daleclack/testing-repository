#include <gtk/gtk.h>

static GtkWidget *video;

static void dialog_response(GtkWidget *widget,int response,GtkWindow *window){
    //Get File and set the file to the mediacontrols
    if(response==GTK_RESPONSE_OK){
        //Get media File and filename
        char *filename=NULL;
        char title[100];
        GFile *file=gtk_file_chooser_get_file(GTK_FILE_CHOOSER(widget));
        gtk_video_set_file(GTK_VIDEO(video),file);
        filename=g_file_get_basename(file);
        sprintf(title,"%s-gtk4-media",filename);
        gtk_window_set_title(GTK_WINDOW(window),title);
        //Free the memory
        g_object_unref(file);
        free(filename);
    }
    gtk_window_destroy(GTK_WINDOW(widget));
    //g_object_unref(widget);
}

static void dialog_open(GtkWidget *widget,GtkWindow *parent){
    //Set a dialog and choose the file
    GtkWidget *dialog;
    GtkFileChooserAction action=GTK_FILE_CHOOSER_ACTION_OPEN;
    dialog=gtk_file_chooser_dialog_new("Open Media File",parent,action,
    "OK",GTK_RESPONSE_OK,"Cancel",GTK_RESPONSE_CANCEL,NULL);
    //Set filter
    GtkFileFilter *filter;
    filter=gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter,"*.mp3");
    gtk_file_filter_add_pattern(filter,"*.mp4");
    gtk_file_filter_add_pattern(filter,"*.wav");
    gtk_file_filter_add_pattern(filter,"*.flac");
    gtk_file_filter_add_pattern(filter,"*.aac");
    gtk_file_filter_add_pattern(filter,"*.m4a");
    gtk_file_filter_add_pattern(filter,"*.3gp");
    gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog),filter);
    g_signal_connect(dialog,"response",G_CALLBACK(dialog_response),parent);
    gtk_widget_show(dialog);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*header,*btnopen;
    //Initalize window
    window=gtk_application_window_new(app);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(window),960,540);
    gtk_window_set_title(GTK_WINDOW(window),"Gtk4 video test");
    //GtkVideo widget
    video=gtk_video_new();
    gtk_window_set_child(GTK_WINDOW(window),video);
    //Header Bar
    header=gtk_header_bar_new();
    gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(header),TRUE);
    gtk_header_bar_set_decoration_layout(GTK_HEADER_BAR(header),"close,minimize,maximize:menu");
    //"Open File" button
    btnopen=gtk_button_new_with_label("Open Media File");
    g_signal_connect(btnopen,"clicked",G_CALLBACK(dialog_open),window);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header),btnopen);
    gtk_window_set_titlebar(GTK_WINDOW(window),header);
    gtk_window_set_focus(GTK_WINDOW(window),btnopen);
    gtk_widget_show(window);
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}