#include "MainWin.h"

static void gtkmain(GtkApplication *app, gpointer user_data){
    MainWin *mainwin = main_win_new(app);
    gtk_window_present(GTK_WINDOW(mainwin));
}

int main(int argc, char **argv)
{
    // Create a GtkApplication instance
    GtkApplication *app = gtk_application_new("org.gtk.daleclack", G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app, "activate", G_CALLBACK(gtkmain), NULL);
    
    // Run the application
    return g_application_run(G_APPLICATION(app), argc, argv);
}