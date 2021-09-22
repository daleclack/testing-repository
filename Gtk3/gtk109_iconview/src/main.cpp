#include <gtk/gtk.h>

enum{
   COL_PATH,
   COL_DISPLAY_NAME,
   COL_PIXBUF,
   COL_IS_DIRECTORY,
   NUM_COLS
};

static GdkPixbuf *file_pixbuf, *folder_pixbuf;
static gchar *parent;
static GtkToolItem *up_button;

static void close_window(GtkWidget *widget,gpointer data){
    gtk_widget_destroy(widget);
    widget=NULL;

    // g_object_unref(file_pixbuf);
    // file_pixbuf=NULL;

    // g_object_unref(folder_pixbuf);
    // folder_pixbuf=NULL;

}

static void gtkmain(GtkApplication* app,gpointer user_data){
    GtkWidget *window,*sw,*icon_view,*vbox,*tool_bar;
    GtkToolItem *home_button;
    GtkListStore *store;

    //Initalize window
    window=gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window),650,400);
    gtk_window_set_title(GTK_WINDOW(window),"Icon View");
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    g_signal_connect(window,"destroy",G_CALLBACK(close_window),NULL);

    //load_pixbufs();

    //Create child widgets
    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);

    tool_bar=gtk_toolbar_new();
    gtk_box_pack_start(GTK_BOX(vbox),tool_bar,FALSE,FALSE,0);

    up_button=gtk_tool_button_new(NULL,NULL);
    gtk_tool_button_set_label(GTK_TOOL_BUTTON(up_button),"_Up");
    gtk_tool_button_set_use_underline(GTK_TOOL_BUTTON(up_button),TRUE);
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(up_button),"go-up");
    gtk_tool_item_set_is_important(up_button,TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(up_button),FALSE);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar),up_button,-1);

    home_button = gtk_tool_button_new(NULL,NULL);
    gtk_tool_button_set_label(GTK_TOOL_BUTTON(home_button),"_Home");
    gtk_tool_button_set_use_underline(GTK_TOOL_BUTTON(home_button),TRUE);
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(home_button),"go-home");
    gtk_tool_item_set_is_important(home_button,TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(home_button),FALSE);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar),home_button,-1);

    sw = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw),GTK_SHADOW_ETCHED_IN);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (sw),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox),sw,TRUE,TRUE, 0);

    gtk_widget_show_all(window);
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    int status=g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    return status;
}
