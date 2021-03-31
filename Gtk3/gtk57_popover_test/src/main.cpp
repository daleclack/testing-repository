#include <gtk/gtk.h>

static void MsgBox(const gchar *msg,gpointer app){
    GtkWidget *dialog,*vbox,*label2;
    GtkWindow *win;
    //Initalize window
    dialog=gtk_dialog_new();
    gtk_window_set_default_size(GTK_WINDOW(dialog),300,150);
    gtk_window_set_icon_name(GTK_WINDOW(dialog),"org.gtk.daleclack");
    win=gtk_application_get_active_window(GTK_APPLICATION(app));
    gtk_window_set_transient_for(GTK_WINDOW(dialog),win);
    gtk_dialog_add_button(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK);
    vbox=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    //label1=gtk_label_new("    ");
    //gtk_box_pack_start(GTK_BOX(vbox),label1,TRUE,TRUE,0);
    label2=gtk_label_new(msg);
    gtk_box_pack_start(GTK_BOX(vbox),label2,TRUE,TRUE,0);
    g_signal_connect_swapped(dialog,"response",G_CALLBACK(gtk_widget_destroy),dialog);
    gtk_widget_show_all(dialog);
}

static void config1_activated(GSimpleAction *action,
                              GVariant      *parameter,
                              gpointer      app)
{
    MsgBox("Config1",app);
}

static void config2_activated(GSimpleAction *action,
                              GVariant      *parameter,
                              gpointer      app)
{
    MsgBox("Config2",app);
}

static void config3_activated(GSimpleAction *action,
                              GVariant      *parameter,
                              gpointer      app)
{
    MsgBox("Config3",app);    
}

static void about_activated(GSimpleAction *action,
                           GVariant      *parameter,
                           gpointer      app)
{
    MsgBox("About gtk57\nA GtkPopover test(Gtk3 Version)",app);
}

static void quit_activated(GSimpleAction *action,
                           GVariant      *parameter,
                           gpointer      app)
{
    g_application_quit(G_APPLICATION(app));
}

static GActionEntry app_entry[] =
{
    {"quit",quit_activated,NULL,NULL,NULL},
    {"about",about_activated,NULL,NULL,NULL},
    {"config1",config1_activated,NULL,NULL,NULL},
    {"config2",config2_activated,NULL,NULL,NULL},
    {"config3",config3_activated,NULL,NULL,NULL}
};

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*header,*menubtn,*popover;
    GtkBuilder *builder=gtk_builder_new_from_resource("/gtk57/menubar.xml");
    GMenuModel *model;
    //Initalize window
    window=gtk_application_window_new(app);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(window),400,240);
    //gtk_window_set_title(GTK_WINDOW(window),"gtk (57)");
    g_action_map_add_action_entries(G_ACTION_MAP(app),app_entry,
                                    G_N_ELEMENTS (app_entry),app);
    //Header bar
    header=gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header),TRUE);
    gtk_header_bar_set_title(GTK_HEADER_BAR(header),"gtk (57)");
    //A application menu
    menubtn=gtk_menu_button_new();
    model=G_MENU_MODEL(gtk_builder_get_object(builder,"app-menu"));
    popover=gtk_popover_new_from_model(menubtn,model);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header),menubtn);
    gtk_menu_button_set_popover(GTK_MENU_BUTTON(menubtn),popover);
    gtk_window_set_titlebar(GTK_WINDOW(window),header);
    gtk_widget_show_all(window);
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}