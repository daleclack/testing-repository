#include "TestWin.h"

struct _TestWin
{
    GtkWindow parent_instance;
    GtkWidget *header;
    GtkWidget *btn_close, *btn_mini;
};

G_DEFINE_TYPE(TestWin, test_win, GTK_TYPE_WINDOW)

static void test_win_hide(TestWin *self)
{
    gtk_widget_set_visible(GTK_WIDGET(self), FALSE);
}

static void test_win_init(TestWin *self)
{
    gtk_window_set_title(GTK_WINDOW(self), "Test Window 1");
    // Create widgets
    self->header = gtk_header_bar_new();
    gtk_widget_set_css_classes(self->header, NULL);
    gtk_widget_add_css_class(self->header, "mytitlebar");
    gtk_window_set_titlebar(GTK_WINDOW(self), self->header);

    // Initalize headerbar
    gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(self->header), FALSE);

    // Add a close button
    self->btn_close = gtk_button_new_with_label("\u00d7");
    gtk_widget_set_css_classes(self->btn_close, NULL);
    gtk_widget_add_css_class(self->btn_close, "ctrl_btn");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(self->header), self->btn_close);

    // Add a minimize button
    self->btn_mini = gtk_button_new_with_label("-");
    gtk_widget_set_css_classes(self->btn_mini, NULL);
    gtk_widget_add_css_class(self->btn_mini, "ctrl_btn");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(self->header), self->btn_mini);

    // Add style for headerbar
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_resource(provider, "/org/gtk/daleclack/style.css");
    gtk_style_context_add_provider_for_display(gtk_widget_get_display(GTK_WIDGET(self)),
                                               GTK_STYLE_PROVIDER(provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_signal_connect_swapped(self->btn_close, "clicked", G_CALLBACK(test_win_hide), self);
    g_signal_connect_swapped(self->btn_mini, "clicked", G_CALLBACK(test_win_hide), self);
}

static void test_win_class_init(TestWinClass *klass)
{
}

TestWin *test_win_new(GtkWindow *parent)
{
    return Test_Win(g_object_new(test_win_get_type(),
                                 "transient-for", parent, NULL));
}
