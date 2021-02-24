#include <cstdlib>
#include <thread>
#include "panel2.h"
#include "win1.h"
#include "game.h"

void add_leftpanel(GtkBuilder *builder,GtkFixed *fixed){
    //Get Left panel
    GtkBuilder *panel2=gtk_builder_new_from_resource("/gtk42/leftpanel.ui");
    GObject *panel=gtk_builder_get_object(panel2,"left_panel");
    //Set start button and image
    GObject *btn_image=gtk_builder_get_object(panel2,"btn_image");
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_resource("/gtk42/icon.png",NULL);
    GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,40,40,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(btn_image),sized);
    //Get popover window
    GObject *popover=gtk_builder_get_object(panel2,"popover1");
    //Button image
    GtkWidget *img_vlc=gtk_image_new_from_resource("/gtk42/vlc.png");
    GtkWidget *img_aud=gtk_image_new_from_resource("/gtk42/audacious.png");
    GtkWidget *img_gedit=gtk_image_new_from_resource("/gtk42/gedit.png");
    //Audacious bin exec
    GObject *btn_audacious=gtk_builder_get_object(panel2,"btnaud");
    gtk_button_set_image(GTK_BUTTON(btn_audacious),img_aud);
    g_signal_connect(btn_audacious,"clicked",G_CALLBACK(btnaud_clicked),NULL);
    g_signal_connect_swapped(btn_audacious,"clicked",G_CALLBACK(gtk_widget_hide),popover);
    //vlc exec button for linux
    GObject *btnvlc=gtk_builder_get_object(panel2,"btnvlc");
    GObject *img_vlc1=gtk_builder_get_object(panel2,"image1");
    gtk_image_set_from_resource(GTK_IMAGE(img_vlc1),"/gtk42/vlc.png");
    g_signal_connect(btnvlc,"clicked",G_CALLBACK(btnvlc_clicked),NULL);
    g_signal_connect_swapped(btnvlc,"clicked",G_CALLBACK(gtk_widget_hide),popover);
    //Start Gedit Text Editor
    GObject *btngedit=gtk_builder_get_object(panel2,"btngedit");
    GObject *img_gedit1=gtk_builder_get_object(panel2,"image2");
    gtk_image_set_from_resource(GTK_IMAGE(img_gedit1),"/gtk42/gedit.png");
    g_signal_connect(btngedit,"clicked",G_CALLBACK(btngedit_clicked),NULL);
    g_signal_connect_swapped(btngedit,"clicked",G_CALLBACK(gtk_widget_hide),popover);
    //Notepad on windows
    GObject *btnnote=gtk_builder_get_object(panel2,"btn_note");
    gtk_button_set_image(GTK_BUTTON(btnnote),img_gedit);
    g_signal_connect(btnnote,"clicked",G_CALLBACK(btnnote_clicked),NULL);
    g_signal_connect_swapped(btnnote,"clicked",G_CALLBACK(gtk_widget_hide),popover);
    //VLC on windows
    GObject *btn_vlc=gtk_builder_get_object(panel2,"btn_vlc");
    gtk_button_set_image(GTK_BUTTON(btn_vlc),img_vlc);
    g_signal_connect(btn_vlc,"clicked",G_CALLBACK(btnvlc_win32),NULL);
    g_signal_connect_swapped(btn_vlc,"clicked",G_CALLBACK(gtk_widget_hide),popover);
    //Get main window
    GObject *window=gtk_builder_get_object(builder,"window");
    //Gtk31 application
    GObject *btngame=gtk_builder_get_object(panel2,"btngame");
    g_signal_connect(btngame,"clicked",G_CALLBACK(gamemain),window);
    g_signal_connect_swapped(btngame,"clicked",G_CALLBACK(gtk_widget_hide),popover);
    //About window
    GObject *btn_about=gtk_builder_get_object(panel2,"btnabout");
    g_signal_connect(btn_about,"clicked",G_CALLBACK(win1_init),window);
    g_signal_connect_swapped(btn_about,"clicked",G_CALLBACK(gtk_widget_hide),popover);
    gtk_fixed_put(fixed,GTK_WIDGET(panel),0,25);
    g_object_unref(pixbuf);
    g_object_unref(sized);
}

void btnvlc_clicked(GtkWidget *widget,gpointer data){
    std::thread first(system,"vlc");
    first.detach();
}

void btngedit_clicked(GtkWidget *widget,gpointer data){
    std::thread second(system,"gedit");
    second.detach();
}

void btnaud_clicked(GtkWidget *widget,gpointer data){
    std::thread third(system,"audacious");
    third.detach();
}

void btnnote_clicked(GtkWidget *widget,gpointer data){
    std::thread fourth(system,"start notepad");
    fourth.detach();
}

void btnvlc_win32(GtkWidget *widget,gpointer data){
    std::thread fifth(system,"start ..\\vlc\\vlc.exe");
    fifth.detach();
}
