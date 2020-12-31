#include "gtkclass.h"

void GtkWin::init(GtkApplication *app,int width,int height){
    window=gtk_application_window_new(app);
    _window=GTK_WINDOW(window);
    gtk_window_set_default_size(_window,width,height);
    gtk_window_set_position(_window,GTK_WIN_POS_CENTER);

    WinHeader header;
    header.header_init("gtk(29)");
    set_titlebar(header.header);
}

void GtkWin::set_titlebar(GtkWidget *titlebar){
    gtk_window_set_titlebar(_window,titlebar);
}

void GtkWin::present(){
    gtk_widget_show_all(window);
}

void WinHeader::header_init(const gchar *title){
    header=gtk_header_bar_new();
    _header=GTK_HEADER_BAR(header);
    gtk_header_bar_set_title(_header,title);
    gtk_header_bar_set_show_close_button(_header,TRUE);
    gtk_header_bar_set_decoration_layout(_header,"close,minimize,maximize:menu");
}
