/*
This is test for wayland support for My GtkUI Project,
which is started in February 2021,
before March 19, 2024, the project only tested with X11 Environment.
(For Wayland DEs, XWayland is used for test, and GDK_BACKEND will be x11)
However, the window management for My GtkUI 5.x and 7.x are unused for wayland protocol,
because the minimized window and default window has the same window state varible,
which cause the issue.
And this is a try for another idea, which is used for My GtkUI original tests in 2020.
*/

#include "MainWin.h"

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