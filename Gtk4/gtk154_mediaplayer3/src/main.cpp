#include "MyMediaPlayer.h"

static void gtkmain(GtkApplication *app, gpointer user_data)
{
    // Create a media player window and run
    MyMediaPlayer *media_player = my_media_player_new(app);
    gtk_window_present(GTK_WINDOW(media_player));
}

int main(int argc, char **argv)
{
    // Create a application and run
    GtkApplication *app;
    app = gtk_application_new("org.gtk.daleclack", G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app, "activate", G_CALLBACK(gtkmain), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
