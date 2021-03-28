#include <gtk/gtk.h>

static void quit_activated (GSimpleAction *action,GVariant *parameter,gpointer app){
    //Quit application
    g_application_quit(G_APPLICATION(app));
}

static void about_activated(GSimpleAction *action,GVariant *parameter,gpointer app){
    //An about dialog
    GtkWindow *win;
    GtkWidget *content_area,*hbox,*dialog=gtk_dialog_new();
    win=gtk_application_get_active_window(GTK_APPLICATION(app));
    gtk_window_set_transient_for(GTK_WINDOW(dialog),win);
    //gtk_window_set_default_size(GTK_WINDOW(dialog),300,150);
    //Get Content area
    gtk_dialog_add_button(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK);
    content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    //Set image for dialog 
    GtkWidget *image=gtk_image_new();
    gtk_widget_set_size_request(image,40,40);
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_resource("/gtk56/icon.png",NULL);
    GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,40,40,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image),sized);
    gtk_box_append(GTK_BOX(hbox),image);
    //Label
    GtkWidget *label=gtk_label_new("About gtk56_gtk4 menu test\n2019-2021 Xe Corporation");
    gtk_box_append(GTK_BOX(hbox),label);
    g_signal_connect_swapped(dialog,"response",G_CALLBACK(gtk_window_destroy),dialog);
    //Add widgets to dialog
    gtk_box_set_baseline_position(GTK_BOX(content_area),GTK_BASELINE_POSITION_BOTTOM);
    gtk_box_append(GTK_BOX(content_area),hbox);
    gtk_widget_show(GTK_WIDGET(dialog));
    g_object_unref(pixbuf);
    g_object_unref(sized);
}

//Menu entrys
static GActionEntry app_entry[]={
    {"quit", quit_activated, NULL, NULL, NULL},
    {"about", about_activated, NULL , NULL , NULL }
};

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*header,*menubar;
    GtkBuilder *builder;
    GMenuModel *model;
    //Link menu with actions
    g_action_map_add_action_entries (G_ACTION_MAP (app),
                                   app_entry, G_N_ELEMENTS (app_entry),
                                   app);
    //Main window
    window=gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window),400,200);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    //Custom title widget
    header=gtk_header_bar_new();
    gtk_header_bar_set_decoration_layout(GTK_HEADER_BAR(header),"close,minimize,maximize:menu");
    gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(header),TRUE);
    //Create a menu and put the menu on the titlebar
    builder=gtk_builder_new_from_resource("/gtk56/menubar.ui");
    model=G_MENU_MODEL(gtk_builder_get_object(builder,"app-menu"));
    menubar=gtk_popover_menu_bar_new_from_model(model);
    gtk_header_bar_set_title_widget(GTK_HEADER_BAR(header),menubar);
    gtk_window_set_titlebar(GTK_WINDOW(window),header);
    gtk_widget_show(window);
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}