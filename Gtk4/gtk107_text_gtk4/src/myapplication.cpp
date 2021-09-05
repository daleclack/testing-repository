#include "myapplication.h"
#include "mywindow.h"

struct _MyApplication{
    GtkApplication parent;
};

G_DEFINE_TYPE(MyApplication,my_application,GTK_TYPE_APPLICATION)

static void my_application_activate(GApplication *app){
    MyWindow *win;
    win=my_window_new(MY_APPLICATION(app));
    gtk_window_present(GTK_WINDOW(win));
}

static void my_application_init(MyApplication *app){
}

static void my_application_class_init(MyApplicationClass *appclass){
    G_APPLICATION_CLASS(appclass)->activate=my_application_activate;
}

MyApplication * my_application_new(){
    return (MyApplication*)g_object_new(MY_APPLICATION_TYPE,
                                        "application-id","org.gtk.daleclack",
                                        "flags",G_APPLICATION_NON_UNIQUE,
                                        NULL);
}
