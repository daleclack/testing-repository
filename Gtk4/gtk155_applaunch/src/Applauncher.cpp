#include "Applauncher.h"
#include "AppView.h"

struct _AppLauncher{
    GtkApplicationWindow parent_instance;
};

G_DEFINE_TYPE(AppLauncher, app_launcher, GTK_TYPE_APPLICATION_WINDOW)

static void app_launcher_init(AppLauncher *self)
{
    GtkWidget *scrolled_window = app_view_new();
    gtk_window_set_default_size(GTK_WINDOW(self), 624, 400);

    // Add list to the window
    gtk_window_set_child(GTK_WINDOW(self), scrolled_window);
}

static void app_launcher_class_init(AppLauncherClass *klass)
{
}

AppLauncher *app_launcher_new(GtkApplication *app){
    return APP_LAUNCHER(g_object_new(app_launcher_get_type(), 
        "application", app, NULL));
}