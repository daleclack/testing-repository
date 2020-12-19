#include "GtkClass.h"

void GtkWin::win_init(int width,int height){
    _window=GTK_WINDOW(main_window);
    gtk_window_set_default_size(_window,width,height);
    gtk_window_set_position(_window,GTK_WIN_POS_CENTER);
}

void GtkWin::set_titlebar(GtkWidget *widget){
    _window=GTK_WINDOW(main_window);
    gtk_window_set_titlebar(_window,widget);
}

void GtkWin::add_widget(GtkWidget *widget){
    gtk_container_add(GTK_CONTAINER(main_window),widget);
}

void GtkWin::show_all(){
    gtk_widget_show_all(main_window);
}

void Winheader::header_init(){
    _header=GTK_HEADER_BAR(header);
    gtk_header_bar_set_decoration_layout(_header,"close,minimize,maximize:menu");
    gtk_header_bar_set_show_close_button(_header,TRUE);
}

void Winheader::pack_start(GtkWidget *child){
    gtk_header_bar_pack_start(_header,child);
}

void Winheader::pack_end(GtkWidget *child){
    gtk_header_bar_pack_end(_header,child);
}

void Winlayout::put(GtkWidget *child,int x,int y){
    gtk_layout_put(GTK_LAYOUT(layout),child,x,y);
}
