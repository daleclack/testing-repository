#include "gtkwin.h"
#include "test.h"

//Initalize GtkButton
void GtkBtn::init(const gchar *str,int width,int height){
    button=gtk_button_new_with_label(str);
    gtk_widget_set_size_request(button,width,height);
}

//Link "clicked" signal
void GtkBtn::signal_clicked(pfun func,gpointer data){
    g_signal_connect(button,"clicked",G_CALLBACK(func),data);
}

//put widget int layout
void Winlayout::put(GtkWidget *child,int x,int y){
    gtk_layout_put(GTK_LAYOUT(layout),child,x,y);
}

//Initalize Gtklayout
void Winlayout::init(){
    GtkBtn button1;
    button1.init("Test",100,50);
    button1.signal_clicked(print,NULL);
    put(button1.button,150,100);
}

//Add widget to window
void GtkWin::add(GtkWidget *widget){
    gtk_container_add(GTK_CONTAINER(window),widget);
}


void GtkWin::win_init(GtkApplication *app,int width,int height){
    //Create a window and set window proprites
    window=gtk_application_window_new(app);
    _window=GTK_WINDOW(window);
    gtk_window_set_default_size(_window,width,height);
    gtk_window_set_position(_window,GTK_WIN_POS_CENTER);
    //Put a layout
    Winlayout layout1;
    layout1.init();
    add(layout1.layout);
}

//Show everything
void GtkWin::show_all(){
    gtk_widget_show_all(window);
}
