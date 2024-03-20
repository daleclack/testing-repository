#include "MainWin.h"
#include "../json_nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

static void gtkmain(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window, *header;
    GtkWidget *btn_close, *btn_mini;
    GtkWidget *img_close, *img_mini;

    // Create widgets
    window = gtk_application_window_new(app);
    header = gtk_header_bar_new();
    gtk_window_set_titlebar(GTK_WINDOW(window), header);

    // Initalize headerbar
    gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(header), FALSE);

    // Add a close button
    btn_close = gtk_button_new_with_label("\u00d7");
    gtk_widget_add_css_class(btn_close, "ctrl_btn");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header), btn_close);

    // Add a minimize button
    btn_mini = gtk_button_new_with_label("-");
    gtk_widget_add_css_class(btn_mini, "ctrl_btn");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header), btn_mini);

    // Add style for headerbar
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_resource(provider, "/org/gtk/daleclack/style.css");
    gtk_style_context_add_provider_for_display(gtk_widget_get_display(window),
                                               GTK_STYLE_PROVIDER(provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_signal_connect_swapped(btn_close, "clicked", G_CALLBACK(gtk_window_close), window);
    g_signal_connect_swapped(btn_mini, "clicked", G_CALLBACK(gtk_window_minimize), window);
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