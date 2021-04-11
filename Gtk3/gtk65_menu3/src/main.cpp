#include <gtk/gtk.h>
#include "src/img7.xpm"

#define WIN_WIDTH 640
#define WIN_HEIGHT 360

//static GtkWidget *background;

static void default_background(int width,int height,gpointer app){
    //Get background widget
    GtkWindow *win=gtk_application_get_active_window((GtkApplication*)app);
    GtkWidget *overlay=gtk_bin_get_child((GtkBin*)win);
    GtkWidget *background=gtk_bin_get_child((GtkBin*)overlay);
    //Change background to default
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_xpm_data(img7);
    GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,width,height,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(background),sized);
    //gtk_picture_set_pixbuf(GTK_PICTURE(background),sized);
    g_object_unref(pixbuf);
    g_object_unref(sized);
}

void set_background(GFile *file1,int width,int height,gpointer app){
    //Get background widget
    GtkWindow *win=gtk_application_get_active_window((GtkApplication*)app);
    GtkWidget *overlay=gtk_bin_get_child((GtkBin*)win);
    GtkWidget *background=gtk_bin_get_child((GtkBin*)overlay);
    //Set a background by a file
    char *filename;
    filename=g_file_get_path(file1);
    //g_print("%s",filename);
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_file(filename,NULL);
    GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,width,height,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(background),sized);
    //gtk_picture_set_pixbuf(GTK_PICTURE(background),sized);
    g_object_unref(pixbuf);
    g_object_unref(sized);
    g_object_unref(file1);
    g_free(filename);
}

static void fileopen(GtkWidget *widget,int response,gpointer app){
    if(response==GTK_RESPONSE_OK){
        GFile *file=gtk_file_chooser_get_file(GTK_FILE_CHOOSER(widget));
        set_background(file,WIN_WIDTH,WIN_HEIGHT,app);
    }
    gtk_widget_destroy(widget);
    //gtk_window_destroy(GTK_WINDOW(widget));
}

static void default_activated(GSimpleAction *action,
                               GVariant      *parmeter,
                               gpointer       app)
{
    default_background(WIN_WIDTH,WIN_HEIGHT,app);
}

static void dialog_activated(GSimpleAction *action,
                             GVariant      *parmeter,
                             gpointer       app)
{
    //Initalize dialog
    GtkWindow *win;
    GtkWidget *dialog;
    GtkFileChooserAction action1=GTK_FILE_CHOOSER_ACTION_OPEN;
    win=gtk_application_get_active_window((GtkApplication*)app);
    dialog=gtk_file_chooser_dialog_new("Choose a image File",win,action1,
    "OK",GTK_RESPONSE_OK,"Cancel",GTK_RESPONSE_CANCEL,NULL);
    //Initalize filefilter
    GtkFileFilter *filter=gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter,"*.png");
    gtk_file_filter_add_pattern(filter,"*.jpg");
    gtk_file_filter_add_pattern(filter,"*.jpeg");
    gtk_file_filter_add_pattern(filter,"*.bmp");
    gtk_file_filter_add_pattern(filter,"*.xpm");
    gtk_file_filter_add_pattern(filter,"*.gif");
    gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog),filter);
    g_signal_connect(dialog,"response",G_CALLBACK(fileopen),app);
    gtk_widget_show(dialog);
}

static void about_activated(GSimpleAction *action,
                            GVariant      *parmeter,
                            gpointer       app)
{
    GtkWindow *win;
    win=gtk_application_get_active_window(GTK_APPLICATION(app));
    const char *authors[]={
        "Dale Clack",
        NULL
    };
    char *version;
    version=g_strdup_printf("1.0\nRunning Against GTK %d.%d.%d",
                            gtk_get_major_version(),
                            gtk_get_minor_version(),
                            gtk_get_micro_version());
    GtkWidget *dialog;
    dialog=gtk_about_dialog_new();
    gtk_show_about_dialog(win,
    "program-name","gtk(65)",
    "version",version,
    "copyright", "© 2019—2021 The Xe Project",
    "comments", "A test program for menu and background",
    "authors",authors,
    "logo-icon-name","gtk64",
    "title","About gtk(65)",
    NULL);
    g_free(version);
}

static void quit_activated(GSimpleAction *action,
                           GVariant      *parmeter,
                           gpointer       app)
{
    g_application_quit(G_APPLICATION(app));
}

static void button_press(GtkGesture *gesture,guint n_press,
                         double x,double y,GtkWidget *popover)
{
    //Get Position
    GdkRectangle rectangle;
    rectangle.x=x;
    rectangle.y=y;
    rectangle.width=1;
    rectangle.height=1;
    //g_print("%f %f\n",x,y);
    gtk_popover_set_pointing_to(GTK_POPOVER(popover),&rectangle);
    //gtk_popover_present(GTK_POPOVER(popover));
    gtk_popover_popup(GTK_POPOVER(popover));
    //g_signal_connect(popover,"closed",G_CALLBACK(g_object_unref),builder);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*overlay,*popover,*draw_area,*background;
    //Initalize main window
    window=gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window),WIN_WIDTH,WIN_HEIGHT);
    gtk_window_set_icon_name(GTK_WINDOW(window),"gtk64");
    //Initalize menu actions
    static GActionEntry entries[]={
        {"quit",quit_activated,NULL,NULL,NULL},
        {"default",default_activated,NULL,NULL,NULL},
        {"about",about_activated,NULL,NULL,NULL},
        {"back",dialog_activated,NULL,NULL,NULL}
    };
    g_action_map_add_action_entries(G_ACTION_MAP(app),entries,
                                    G_N_ELEMENTS(entries),app);
    //Overlay widget
    overlay=gtk_overlay_new();
    //Background
    //background=gtk_picture_new();
    background=gtk_image_new();
    gtk_container_add((GtkContainer*)overlay,background);
    //gtk_overlay_set_child(GTK_OVERLAY(overlay),background);
    draw_area=gtk_drawing_area_new();
    gtk_overlay_add_overlay((GtkOverlay*)overlay,draw_area);
    //Initalize menu
    GtkBuilder *builder;
    builder=gtk_builder_new_from_resource("/gtk64/appmenu.xml");
    GMenuModel *model;
    //Create a menu
    model=G_MENU_MODEL(gtk_builder_get_object(builder,"app-menu"));
    popover=gtk_popover_new_from_model(draw_area,model);
    gtk_widget_set_valign(popover,GTK_ALIGN_END);
    //popover=gtk_popover_menu_new_from_model(model);
    //gtk_popover_set_has_arrow(GTK_POPOVER(popover),FALSE);
    //gtk_widget_set_parent(popover,overlay);
    g_object_unref(model);
    //Initalize a Gesture
    GtkGesture *press;
    
    //press=gtk_gesture_click_new();
    press=gtk_gesture_multi_press_new(draw_area);
    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(press),GDK_BUTTON_SECONDARY);
    g_signal_connect(press,"pressed",G_CALLBACK(button_press),popover);
    //gtk_widget_add_controller(overlay,GTK_EVENT_CONTROLLER(press));

    //gtk_window_set_child(GTK_WINDOW(window),overlay);
    gtk_container_add((GtkContainer*)window,overlay);
    default_background(WIN_WIDTH,WIN_HEIGHT,app);
    gtk_widget_show_all(window);
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}