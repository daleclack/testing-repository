#include "MainWin.h"

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
    btn_close = gtk_button_new();
    
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header), btn_close);

    // Add a minimize button
    btn_mini = gtk_button_new();
    
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

    // Get Scale factor
    GdkSurface *surface = gtk_native_get_surface(GTK_NATIVE(window));
    double scale = gdk_surface_get_scale(surface);
    g_print("%f\n", scale);

    img_close = gtk_image_new_from_icon_name("win_close");
    gtk_image_set_pixel_size(GTK_IMAGE(img_close), 12 / scale);
    gtk_button_set_child(GTK_BUTTON(btn_close), img_close);

    img_mini = gtk_image_new_from_icon_name("win_minimize");
    gtk_image_set_pixel_size(GTK_IMAGE(img_mini), 12 / scale);
    gtk_button_set_child(GTK_BUTTON(btn_mini), img_mini);
}

int main(int argc, char **argv)
{
    // Create a app and run
    GtkApplication *app = gtk_application_new("org.gtk.daleclack", G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app, "activate", G_CALLBACK(gtkmain), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}