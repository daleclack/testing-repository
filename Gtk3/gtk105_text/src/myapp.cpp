#include "myapp.h"
#include "mywindow.h"
#include "myprefs.h"

struct _MyApp{
    GtkApplication parent;
};

G_DEFINE_TYPE(MyApp,my_app,GTK_TYPE_APPLICATION)

static void my_app_activate(GApplication *app){
    //When Application activate,create a window
    MyWindow *win;
    win=my_window_new(MY_APP(app));
    gtk_window_present(GTK_WINDOW(win));
}

static void my_app_open(GApplication *app,
                        GFile **files,
                        gint n_files,
                        const gchar *hint)
{
    GList *windows;
    MyWindow *win;

    //Get Windows for application
    windows=gtk_application_get_windows(GTK_APPLICATION(app));
    if(windows){
        win=MY_WINDOW(windows->data);
    }else{
        win=my_window_new(MY_APP(app));
    }

    for(int i=0;i<n_files;i++){
        my_window_open(win,files[i]);
    }

    //Show the window
    gtk_window_present(GTK_WINDOW(win));
}

static void preference_activated(GSimpleAction *action,
                                 GVariant      *parameter,
                                 gpointer       app)
{
    //g_print("Preference Activated\n");
    MyPrefs * prefs;
    GtkWindow * win;

    win=gtk_application_get_active_window(GTK_APPLICATION(app));
    prefs=my_prefs_new(MY_WINDOW(win));
    gtk_window_present(GTK_WINDOW(prefs));
}

static void quit_activated(GSimpleAction *action,
                           GVariant      *parameter,
                           gpointer       app)
{
    g_application_quit(G_APPLICATION(app));
}

static GActionEntry entries[]={
    {"preferences",preference_activated,NULL,NULL,NULL},
    {"quit",quit_activated,NULL,NULL,NULL}
};

static void my_app_startup(GApplication *app){
    
    const gchar * quit_accels[2]={"<Ctrl>Q",NULL};

    //Start The Application
    G_APPLICATION_CLASS(my_app_parent_class)->startup(app);

    g_action_map_add_action_entries(G_ACTION_MAP(app),entries,
                                    G_N_ELEMENTS(entries),app);
    gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.quit",quit_accels);
}

static void my_app_init(MyApp *app){
}

static void my_app_class_init(MyAppClass *class1){
    G_APPLICATION_CLASS(class1)->activate=my_app_activate;
    G_APPLICATION_CLASS(class1)->open=my_app_open;
    G_APPLICATION_CLASS(class1)->startup=my_app_startup;
}

MyApp * my_app_new(){
    return (MyApp*)g_object_new(MY_APP_TYPE,
                        "application-id","org.gtk.daleclack",
                        "flags",G_APPLICATION_HANDLES_OPEN,
                        NULL);
}

