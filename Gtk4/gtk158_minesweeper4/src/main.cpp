#include "MineSweeper.h"

static void gtkmain(GtkApplication *app, gpointer user_data)
{
    // Create MineSweeper window
    MineSweeper *mine_sweeper = mine_sweeper_new();
    gtk_application_add_window(app, GTK_WINDOW(mine_sweeper));
    gtk_window_present(GTK_WINDOW(mine_sweeper));
}

int main(int argc, char **argv)
{
    // Create a app and run
    GtkApplication *app;
    app = gtk_application_new("org.gtk.daleclack", G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app, "activate", G_CALLBACK(gtkmain), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}