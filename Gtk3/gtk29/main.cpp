#include <gtk/gtk.h>
#include "360.xpm"

static const gchar *info[5]={
"This is a gtkbuilder test application",
"The Gtk3 is a cross platform and a good graphics library",
"We are going to bring the Gtk3 and Gtk4 to every developer",
"The GUN/Linux is a good operation system",
"After that,Please Link the application to your project"
};
gint info_num=0;
GObject *btn_pre;
GObject *btn_next;

void BtnOK_click(GtkWidget *widget,gpointer data){
    gtk_widget_destroy(GTK_WIDGET(data));
}

void BtnPre_click(GtkWidget *widget,gpointer data){
    info_num-=1;
    if(info_num==-1) info_num=0;
    if(info_num==0){
        gtk_widget_set_sensitive(GTK_WIDGET(btn_pre),FALSE);
    }
    gtk_label_set_label(GTK_LABEL(data),info[info_num]);
    gtk_widget_set_sensitive(GTK_WIDGET(btn_next),TRUE);
}

void BtnNext_click(GtkWidget *widget,gpointer data){
    info_num+=1;
    if(info_num==4){
        gtk_widget_set_sensitive(GTK_WIDGET(btn_next),FALSE);
    }
    gtk_label_set_label(GTK_LABEL(data),info[info_num]);
    gtk_widget_set_sensitive(GTK_WIDGET(btn_pre),TRUE);
}

void image_init(GtkImage *img){
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_xpm_data(_60);
    GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,40,40,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(img,sized);
}

void window_init(GtkWindow *window1){
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_xpm_data(_60);
    gtk_window_set_icon(window1,pixbuf);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkBuilder *builder;
    builder=gtk_builder_new();
    gtk_builder_add_from_resource(builder,"/gtk29/window.ui",NULL);
    GtkBuilder *builder1=gtk_builder_new_from_resource("/gtk29/header.ui");

    GObject *window;
    GObject *header=gtk_builder_get_object(builder1,"header");
    window=gtk_builder_get_object(builder,"window");
    gtk_application_add_window(app,GTK_WINDOW(window));
    gtk_window_set_titlebar(GTK_WINDOW(window),GTK_WIDGET(header));
    window_init(GTK_WINDOW(window));

    GObject *label=gtk_builder_get_object(builder,"label1");
    gtk_label_set_label(GTK_LABEL(label),info[0]);
    GObject *image=gtk_builder_get_object(builder,"image1");
    image_init(GTK_IMAGE(image));
    btn_pre=gtk_builder_get_object(builder,"pre_button");
    g_signal_connect(btn_pre,"clicked",G_CALLBACK(BtnPre_click),(gpointer)label);
    btn_next=gtk_builder_get_object(builder,"btn_next");
    g_signal_connect(btn_next,"clicked",G_CALLBACK(BtnNext_click),(gpointer)label);
    GObject *btn_OK=gtk_builder_get_object(builder,"btn_OK");
    g_signal_connect(btn_OK,"clicked",G_CALLBACK(BtnOK_click),(gpointer)window);
    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    app=gtk_application_new("com.github.daleclack.gtk29",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
