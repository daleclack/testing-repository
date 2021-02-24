#include <gtk/gtk.h>
#include <ctime>
#include <cstdlib>
#include <cstring>

GObject *button[4];
GObject *label;
const char *btn_index[4]={"0","1","2","3"};
int flag;

void btn_click(GtkWidget *widget,gpointer data){
    //Get image
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_resource("/gtk31/icon.jpg",NULL);
    GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,50,50,GDK_INTERP_BILINEAR);
    GtkWidget *image=gtk_image_new_from_pixbuf(sized);
    //Get button index
    char str[2];
    strcpy(str,(char*)data);
    //Set a image to the flag button and judge
    gtk_button_set_image((GtkButton*)button[flag],image);
    if(flag==str[0]-48){
        gtk_label_set_label(GTK_LABEL(label),"Good luck!");
    }else{
        gtk_label_set_label(GTK_LABEL(label),"Flag missed.");
    }
    for(int i=0;i<4;i++){
        gtk_widget_set_sensitive(GTK_WIDGET(button[i]),FALSE);
    }
    //Free GdkPixbuf memory
    g_object_unref(pixbuf);
    g_object_unref(sized);
}

void buttons_init(GtkBuilder *builder){
    //Initalize buttons
    for(int i=0;i<4;i++){
        char str[6];
        sprintf(str,"btn_%d",i+1);
        button[i]=gtk_builder_get_object(builder,str);
        g_signal_connect(button[i],"clicked",G_CALLBACK(btn_click),(gpointer)btn_index[i]);
    }
}

void btngo_click(GtkWidget *widget,gpointer data){
    //Reinitalize the buttons and the flag
    gtk_label_set_label(GTK_LABEL(label),"Select a button");
    for(int i=0;i<4;i++){
        gtk_widget_set_sensitive(GTK_WIDGET(button[i]),TRUE);
        gtk_button_set_image((GtkButton*)button[i],NULL);
    }
    srand((unsigned)time(NULL));
    int x=rand();
    flag=x%4;
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    //Get objects from the Gtkbuilder and initalize the application
    GtkBuilder *builder=gtk_builder_new();
    GObject *window;
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_resource("/gtk31/icon.jpg",NULL);
    gtk_builder_add_from_resource(builder,"/gtk31/window.ui",NULL);
    window=gtk_builder_get_object(builder,"window");
    gtk_application_add_window(app,GTK_WINDOW(window));
    gtk_window_set_icon(GTK_WINDOW(window),pixbuf);
    //Get buttons from GtkBuilder
    buttons_init(builder);
    GObject *btn_go=gtk_builder_get_object(builder,"btn_go");
    g_signal_connect(btn_go,"clicked",G_CALLBACK(btngo_click),(gpointer)builder);
    GObject *btn_exit=gtk_builder_get_object(builder,"btn_exit");
    g_signal_connect_swapped(btn_exit,"clicked",G_CALLBACK(gtk_widget_destroy),GTK_WIDGET(window));
    label=gtk_builder_get_object(builder,"label");
    //Initalize the flag
    srand((unsigned)time(NULL));
    int x=rand();
    flag=x%4;

    gtk_widget_show_all(GTK_WIDGET(window));
    g_object_unref(pixbuf);
}

int main(int argc,char *argv[]){
    //Create and start a application
    GtkApplication *app;
    app=gtk_application_new("com.github.daleclack.gtk31",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
