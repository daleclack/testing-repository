#include "FileManager.h"

static void gtkmain(GtkApplication *app, gpointer user_data){
    // Create a main window
    FileManager *file_win = file_manager_new();

    // Add the window to the application
    gtk_application_add_window(app, GTK_WINDOW(file_win));

    // Show the window
    gtk_window_present(GTK_WINDOW(file_win));
}

int main(int argc, char **argv)
{
    // Create a application and run
    GtkApplication *app = gtk_application_new("org.gtk.daleclack", G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app, "activate", G_CALLBACK(gtkmain), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
