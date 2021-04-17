#include <gtk/gtk.h>

static GtkWidget *video;

static void clear_activated(GSimpleAction *action,
                            GVariant      *parmeter,
                            gpointer       app)
{
   GFile *file=gtk_video_get_file((GtkVideo*)video);
   if(file!=NULL) g_object_unref(file);
   gtk_video_set_file((GtkVideo*)video,NULL);
   //Set window title
   GtkWindow *win=gtk_application_get_active_window((GtkApplication*)app);
   gtk_window_set_title(win,"Gtk4 Media");
}

static void pause_activated(GSimpleAction *action,
                            GVariant      *parmeter,
                            gpointer       app)
{
    GtkMediaStream *media=gtk_video_get_media_stream((GtkVideo*)video);
    if(media!=NULL){
        gtk_media_stream_pause(media);
        g_object_unref(media);
    }
   
}

static void play_activated(GSimpleAction *action,
                           GVariant      *parmeter,
                           gpointer       app)
{
    GtkMediaStream *media=gtk_video_get_media_stream((GtkVideo*)video);
    
    if(media!=NULL){
        gtk_media_stream_play(media);
        g_object_unref(media);
    } 
}

static void quit_activated(GSimpleAction *action,
                           GVariant      *parmeter,
                           gpointer       app)
{
    g_application_quit(G_APPLICATION(app));
}

static void about_activated(GSimpleAction *action,
                            GVariant      *parmeter,
                            gpointer       app)
{
    GtkWindow *win;
    win=gtk_application_get_active_window((GtkApplication*)app);
    const char *authors[]={
        "Dale Clack",
        NULL
    };
    //Program version
    char *version;
    version=g_strdup_printf("2.0\nRunning Against GTK %d.%d.%d",
                            gtk_get_major_version(),
                            gtk_get_minor_version(),
                            gtk_get_micro_version());
    GtkWidget *dialog;
    dialog=gtk_dialog_new();
    gtk_show_about_dialog(win,
    "program-name","Gtk4 Media",
    "version",version,
    "copyright", "© 2019—2021 The Xe Project",
    "comments","A Simple Media Player",
    "authors",authors,
    "logo-icon-name","gtk68",
    "title","About Gtk4 Media",
    NULL);
}

static void dialog_response(GtkWidget *widget,int response,GtkWindow *window){
    //Get File and set the file to the mediacontrols
    if(response==GTK_RESPONSE_OK){
        //Get media File and filename
        char *filename=NULL;
        //GtkMediaStream *media;
        GFile *file=gtk_file_chooser_get_file(GTK_FILE_CHOOSER(widget));
        //media=gtk_media_file_new_for_file(file);
        //gtk_video_set_media_stream(GTK_VIDEO(video),media);
        gtk_video_set_file(GTK_VIDEO(video),file);
        filename=g_file_get_basename(file);
        gtk_window_set_title(GTK_WINDOW(window),filename);
        //Free the memory
        //gtk_media_file_clear(GTK_MEDIA_FILE(media));
        g_object_unref(file);
        free(filename);
    }
    gtk_window_destroy(GTK_WINDOW(widget));
    //g_object_unref(widget);
}

static void open_activated(GSimpleAction *action,
                           GVariant      *parmeter,
                           gpointer       app)
{
    //Set a dialog and choose the file
    GtkWindow *parent=gtk_application_get_active_window((GtkApplication*)app);
    GtkWidget *dialog;
    GtkFileChooserAction action1=GTK_FILE_CHOOSER_ACTION_OPEN;
    dialog=gtk_file_chooser_dialog_new("Open Media File",parent,action1,
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
    g_signal_connect(dialog,"response",G_CALLBACK(dialog_response),parent);
    gtk_widget_show(dialog);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*header,*popover,*menubtn;
    //Initalize window
    window=gtk_application_window_new(app);
    gtk_window_set_icon_name(GTK_WINDOW(window),"gtk68");
    gtk_window_set_default_size(GTK_WINDOW(window),480,270);
    gtk_window_set_title(GTK_WINDOW(window),"Gtk4 Media");
    //vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    //GMenuModel and actions
    GActionEntry entries[]={
        {"quit",quit_activated,NULL,NULL,NULL},
        {"open",open_activated,NULL,NULL,NULL},
        {"play",play_activated,NULL,NULL,NULL},
        {"pause",pause_activated,NULL,NULL,NULL},
        {"clear",clear_activated,NULL,NULL,NULL},
        {"about",about_activated,NULL,NULL,NULL}
    };
    GtkBuilder *builder=gtk_builder_new_from_resource("/gtk68/appmenu.xml");
    GMenuModel *model=(GMenuModel*)gtk_builder_get_object(builder,"app-menu");
    g_action_map_add_action_entries(G_ACTION_MAP(app),entries,G_N_ELEMENTS(entries),app);
    //GtkVideo widget
    video=gtk_video_new();
    gtk_video_set_autoplay((GtkVideo*)video,TRUE);
    gtk_window_set_child(GTK_WINDOW(window),video);
    //gtk_box_append(GTK_BOX(vbox),mediacontrol);
    //Header Bar
    header=gtk_header_bar_new();
    gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(header),TRUE);
    gtk_header_bar_set_decoration_layout(GTK_HEADER_BAR(header),"close,minimize,maximize:menu");
    //Menu to control files
    menubtn=gtk_menu_button_new();
    popover=gtk_popover_menu_new_from_model(model);
    gtk_widget_set_halign(popover,GTK_ALIGN_END);
    gtk_menu_button_set_popover((GtkMenuButton*)menubtn,popover);
    
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header),menubtn);
    gtk_window_set_titlebar(GTK_WINDOW(window),header);
    //gtk_window_set_focus(GTK_WINDOW(window),menubtn);
    gtk_widget_show(window);
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    int status;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    return status;
}
