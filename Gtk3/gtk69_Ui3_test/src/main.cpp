#include <gtk/gtk.h>
#include "winconf.h"
#include "img7.xpm"

static GtkWidget *window1=NULL,*win1_image;

static void win1_destroy(GtkWidget *widget,gpointer data){
    gtk_widget_destroy(window1);
    window1=NULL;
    //GtkWidget *image=(GtkWidget*)gtk_builder_get_object(panel2,"image2");
    gtk_image_set_from_icon_name((GtkImage*)win1_image,"win1",GTK_ICON_SIZE_BUTTON);
}

static GtkWidget *win1_init(GtkWindow *parent){
    //Initalize window1
    GtkWidget *win1,*btn_mini,*btn_close,*img_mini,*img_close;
    GtkBuilder *builder=gtk_builder_new_from_resource("/gtk69/win1.ui");
    win1=(GtkWidget*)gtk_builder_get_object(builder,"win1");
    gtk_window_set_transient_for((GtkWindow*)win1,parent);
    gtk_window_set_icon_name((GtkWindow*)win1,"win1");
    img_mini=(GtkWidget*)gtk_builder_get_object(builder,"image1");
    gtk_image_set_from_icon_name(GTK_IMAGE(img_mini),"window-minimize",GTK_ICON_SIZE_BUTTON);
    btn_mini=(GtkWidget*)gtk_builder_get_object(builder,"btn_mini");
    g_signal_connect_swapped(btn_mini,"clicked",G_CALLBACK(gtk_widget_hide),win1);
    img_close=(GtkWidget*)gtk_builder_get_object(builder,"image2");
    gtk_image_set_from_icon_name(GTK_IMAGE(img_close),"window-close",GTK_ICON_SIZE_BUTTON);
    btn_close=(GtkWidget*)gtk_builder_get_object(builder,"btn_close");
    g_signal_connect(btn_close,"clicked",G_CALLBACK(win1_destroy),win1);
    g_object_unref(builder);
    return win1;
}

static void win1_activate(GtkWidget *widget,GtkBuilder *builder){
    //The Open button for win1
    GtkWindow *win_1=(GtkWindow*)gtk_builder_get_object(builder,"window");
    if(window1==NULL){
        window1=win1_init(win_1);
        gtk_window_set_icon_name((GtkWindow*)window1,"win1");
        win1_image=(GtkWidget*)gtk_builder_get_object(builder,"image2");
        gtk_image_set_from_icon_name((GtkImage*)win1_image,"win1_running",GTK_ICON_SIZE_BUTTON);
        gtk_widget_show_all(window1);
        g_signal_connect(window1,"destroy",G_CALLBACK(win1_destroy),NULL);
    }
}

static void win1_ctrl(GtkWidget *widget,GtkBuilder *builder){
    //The Control button for win on taskbar
    GtkWindow *win_2=(GtkWindow*)gtk_builder_get_object(builder,"window");
    if(window1==NULL){
        win1_image=(GtkWidget*)gtk_builder_get_object(builder,"image2");
        window1=win1_init(win_2);
        gtk_widget_show_all(window1);
        gtk_image_set_from_icon_name((GtkImage*)win1_image,"win1_running",GTK_ICON_SIZE_BUTTON);
        g_signal_connect(window1,"destroy",G_CALLBACK(win1_destroy),NULL);
    }else{
        gboolean is_show=gtk_widget_get_visible(window1);
        if(is_show==TRUE) gtk_widget_hide(window1);
        else gtk_widget_show_all(window1);
    }
}

static void set_background(GtkWidget *back,int width,int height){
    //Set a background for window
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_xpm_data(img7);
    GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,width,height,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf((GtkImage*)back,sized);
    g_object_unref(pixbuf);
    g_object_unref(sized);
}

static void add_panel(GtkWidget *overlay,GtkBuilder *builder){
    GtkWindow *win=(GtkWindow*)gtk_builder_get_object(builder,"window");
    GtkWidget *panel1,*img_panel,*img_win1,*btn_win1,*panel_win1,*btn_size,*btn_exit;
    //Get Panel1 and add the panel to window
    panel1=(GtkWidget*)gtk_builder_get_object(builder,"panelbox");
    //Main panel button
    img_panel=(GtkWidget*)gtk_builder_get_object(builder,"image1");
    gtk_image_set_from_icon_name(GTK_IMAGE(img_panel),"gtk69",GTK_ICON_SIZE_BUTTON);
    //Window1 button on menu and panel
    img_win1=(GtkWidget*)gtk_builder_get_object(builder,"image2");
    gtk_image_set_from_icon_name(GTK_IMAGE(img_win1),"win1",GTK_ICON_SIZE_BUTTON);
    panel_win1=(GtkWidget*)gtk_builder_get_object(builder,"panel_win1");
    btn_win1=(GtkWidget*)gtk_builder_get_object(builder,"btn_win1");
    g_signal_connect(panel_win1,"clicked",G_CALLBACK(win1_ctrl),builder);
    g_signal_connect(btn_win1,"clicked",G_CALLBACK(win1_activate),builder);
    //Window Size config
    btn_size=(GtkWidget*)gtk_builder_get_object(builder,"btnsize");
    g_signal_connect(btn_size,"clicked",G_CALLBACK(conf_dialog),win);
    //Exit
    btn_exit=(GtkWidget*)gtk_builder_get_object(builder,"btnExit");
    g_signal_connect_swapped(btn_exit,"clicked",G_CALLBACK(gtk_widget_destroy),win);
    gtk_widget_set_halign(panel1,GTK_ALIGN_START);
    gtk_widget_set_valign(panel1,GTK_ALIGN_START);
    gtk_overlay_add_overlay((GtkOverlay*)overlay,panel1);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkBuilder *builder=gtk_builder_new_from_resource("/gtk69/window.ui");
    GtkWidget *window,*background,*overlay;
    int width=640,height=360;
    get_config(&width,&height);
    //Get Objects and initalize window
    window=(GtkWidget*)gtk_builder_get_object(builder,"window");
    gtk_window_set_icon_name(GTK_WINDOW(window),"gtk69");
    gtk_window_set_default_size(GTK_WINDOW(window),width,height);
    //Background
    background=(GtkWidget*)gtk_builder_get_object(builder,"background");
    set_background(background,width,height);
    //Add panel
    overlay=(GtkWidget*)gtk_builder_get_object(builder,"overlay");
    add_panel(overlay,builder);
    gtk_application_add_window(app,GTK_WINDOW(window));
    gtk_widget_show_all(window);
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
