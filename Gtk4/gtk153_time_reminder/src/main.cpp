#include "MyReminder.h"

static void gtkmain(GtkApplication *app, gpointer user_data)
{
    // Create main window and present
    MyReminder *window = my_reminder_new(app);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
    // Create a gtk application
    GtkApplication *app = gtk_application_new("org.gtk.daleclack", G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app, "activate", G_CALLBACK(gtkmain), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
