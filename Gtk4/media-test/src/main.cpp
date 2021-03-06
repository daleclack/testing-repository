#include <gtk/gtk.h>

static GtkWidget *mediacontrol;

void dialog_response(GtkWidget *widget,int response,gpointer data){
    //Get File and set the file to the mediacontrols
    if(response==GTK_RESPONSE_OK){
        GFile *file=gtk_file_chooser_get_file(GTK_FILE_CHOOSER(widget));
        GtkMediaStream *media=gtk_media_file_new_for_file(file);
        gtk_media_controls_set_media_stream(GTK_MEDIA_CONTROLS(mediacontrol),media);
    }
    gtk_window_destroy(GTK_WINDOW(widget));
}

void dialog_open(GtkWidget *widget,GtkWindow *parent){
    //Set a dialog and choose the file
    GtkWidget *dialog;
    GtkFileChooserAction action=GTK_FILE_CHOOSER_ACTION_OPEN;
    dialog=gtk_file_chooser_dialog_new("Open Media File",parent,action,
    "OK",GTK_RESPONSE_OK,"Cancel",GTK_RESPONSE_CANCEL,NULL);
    //Set filter
    GtkFileFilter *filter;
    filter=gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter,"*.mp3");
    gtk_file_filter_add_pattern(filter,"*.wav");
    gtk_file_filter_add_pattern(filter,"*.flac");
    gtk_file_filter_add_pattern(filter,"*.aac");
    gtk_file_filter_add_pattern(filter,"*.m4a");
    gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog),filter);
    g_signal_connect(dialog,"response",G_CALLBACK(dialog_response),NULL);
    gtk_widget_show(dialog);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*vbox,*btnopen;
    //Initalize window
    window=gtk_application_window_new(app);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(window),400,20);
    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    //Media controls
    mediacontrol=gtk_media_controls_new(NULL);
    gtk_box_append(GTK_BOX(vbox),mediacontrol);
    //"Open File" button
    btnopen=gtk_button_new_with_label("Open Media File");
    g_signal_connect(btnopen,"clicked",G_CALLBACK(dialog_open),window);
    gtk_box_append(GTK_BOX(vbox),btnopen);
    gtk_window_set_child(GTK_WINDOW(window),vbox);
    gtk_widget_show(window);
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
