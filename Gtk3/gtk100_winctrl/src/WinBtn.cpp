#include "WinBtn.h"

struct _WinBtn{
    GtkButton parent;
    GtkApplication *app;
};

G_DEFINE_TYPE(WinBtn,win_btn,GTK_TYPE_BUTTON)

static void win_btn_clicked(GtkButton *button){
    GtkWindow *win=gtk_application_get_active_window(WIN_BTN(button)->app);
    GdkWindow *gdk_win=gtk_widget_get_window(GTK_WIDGET(win));
    if(gdk_win){
        GdkWindowState state=gdk_window_get_state(gdk_win);
        switch(state){
            case GDK_WINDOW_STATE_ICONIFIED:
                gtk_window_deiconify(win);
                break;
            case GDK_WINDOW_STATE_WITHDRAWN:
                gtk_widget_show_all(GTK_WIDGET(win));
                break;
            default:
                gtk_window_iconify(win);
        }
    }else{
        gtk_widget_show_all(GTK_WIDGET(win));
    }
}

static void win_btn_init(WinBtn *btn1){

}

static void win_btn_class_init(WinBtnClass *class1){
    GTK_BUTTON_CLASS(class1)->clicked=win_btn_clicked;
}

WinBtn * win_btn_new(){
    return WIN_BTN(g_object_new(WIN_BTN_TYPE,NULL));
}

void win_btn_set_application(WinBtn *btn1,GtkApplication *app1){
    btn1->app=app1;
}
