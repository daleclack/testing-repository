#include <gtk/gtk.h>
#include <ctime>

void change_clicked(GtkWidget *widget,GtkBuilder *builder){
    //Get buttons
    GObject *btn[2];
    btn[0]=gtk_builder_get_object(builder,"btn1");
    btn[1]=gtk_builder_get_object(builder,"btn2");
    gtk_button_set_always_show_image(GTK_BUTTON(btn[0]),TRUE);
    gtk_button_set_always_show_image(GTK_BUTTON(btn[1]),TRUE);
    //Clear image
    gtk_button_set_image(GTK_BUTTON(btn[0]),NULL);
    gtk_button_set_image(GTK_BUTTON(btn[1]),NULL);
    //Get index
    srand((unsigned)time(NULL));
    int index=rand();
    index%=2;
    //Set image for button
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_file_at_scale("res/icon.jpg",40,40,FALSE,NULL);
    GtkWidget *image=gtk_image_new_from_pixbuf(pixbuf);
    gtk_button_set_image(GTK_BUTTON(btn[index]),image);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    //Initalize window
    GtkBuilder *builder=gtk_builder_new_from_file("res/window.ui");
    GObject *window=gtk_builder_get_object(builder,"window");
    gtk_window_set_icon_from_file(GTK_WINDOW(window),"res/icon.jpg",NULL);
    gtk_application_add_window(app,GTK_WINDOW(window));
    //"Change" button
    GObject *btn_change=gtk_builder_get_object(builder,"btnchange");
    g_signal_connect(btn_change,"clicked",G_CALLBACK(change_clicked),builder);
    //Exit button
    GObject *btn_exit=gtk_builder_get_object(builder,"btnexit");
    g_signal_connect_swapped(btn_exit,"clicked",G_CALLBACK(gtk_widget_destroy),window);
    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    app=gtk_application_new("com.github.daleclack.gtk37",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
