#include "MainWin.h"

static void gtkmain(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window, *header;

    // Create widgets
    window = gtk_application_window_new(app);
    header = gtk_header_bar_new();
    gtk_window_set_titlebar(GTK_WINDOW(window), header);

    // Add style for headerbar
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_resource(provider, "/org/gtk/daleclack/style.css");
    gtk_style_context_add_provider_for_display(gtk_widget_get_display(window),
                                               GTK_STYLE_PROVIDER(provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

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