#include "Applauncher.h"

static void gtkmain(GtkApplication *app, gpointer user_data)
{
    AppLauncher *launcher = app_launcher_new(app);
    gtk_window_present(GTK_WINDOW(launcher));
}

int main(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new("org.gtk.daleclack", G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app, "activate", G_CALLBACK(gtkmain), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
