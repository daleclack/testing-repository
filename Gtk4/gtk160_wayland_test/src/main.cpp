#include "MainWin.h"
#include "../json_nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

static void gtkmain(GtkApplication *app, gpointer user_data)
{
    // Create window
    MainWin *window = main_win_new(app);
    // show the window
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
    // Create a app and run
    GtkApplication *app = gtk_application_new("org.gtk.daleclack", G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app, "activate", G_CALLBACK(gtkmain), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}