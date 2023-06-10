#include "MyPrefs.h"

static void gtkmain(GtkApplication *app, gpointer data)
{
    GtkWidget *window, *overlay, *main_pic, *btn_back;
    GtkWindow *_window;
    GtkOverlay *_overlay;
    GtkWidget *prefs_win;
    // Create a main window and initalize
    window = gtk_application_window_new(app);
    _window = GTK_WINDOW(window);
    gtk_window_set_icon_name(_window, "org.gtk.daleclack");
    gtk_window_set_title(_window, "Background Prefs Test");
    gtk_window_set_default_size(_window, 1024, 576);

    // Overlay to pack the background and button
    overlay = gtk_overlay_new();
    gtk_widget_set_hexpand(overlay, TRUE);
    gtk_widget_set_vexpand(overlay, TRUE);
    _overlay = GTK_OVERLAY(overlay);

    // Add background widget
    main_pic = gtk_picture_new();
    gtk_widget_set_hexpand(main_pic, TRUE);
    gtk_widget_set_vexpand(main_pic, TRUE);
    gtk_overlay_set_child(_overlay, main_pic);

    // Add a button
    btn_back = gtk_button_new_with_label("Prefs");
    gtk_button_set_has_frame(GTK_BUTTON(btn_back), FALSE);
    gtk_widget_set_halign(btn_back, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(btn_back, GTK_ALIGN_CENTER);
    gtk_overlay_add_overlay(_overlay, btn_back);

    // Creata prefs window
    prefs_win = my_prefs_new(main_pic, _window);
    g_signal_connect_swapped(btn_back, "clicked", G_CALLBACK(gtk_window_present), prefs_win);

    gtk_window_set_child(_window, overlay);
    gtk_window_present(_window);
}

int main(int argc, char **argv)
{
    // Create a application and run
    GtkApplication *app = gtk_application_new("org.gtk.daleclack", G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app, "activate", G_CALLBACK(gtkmain), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}