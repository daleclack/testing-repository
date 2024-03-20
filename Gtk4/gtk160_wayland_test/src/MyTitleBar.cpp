#include "MyTitleBar.h"

struct _MyTitleBar
{
    GObject parent_instance;
    GtkWidget *ctrl_window;
    GtkWidget *header;
    GtkWidget *btn_close, *btn_mini;
};

G_DEFINE_TYPE(MyTitleBar, my_titlebar, G_TYPE_OBJECT)

static void ctrl_win_hide(MyTitleBar *self)
{
    gtk_widget_set_visible(self->ctrl_window, FALSE);
}

static void ctrl_win_close(MyTitleBar *self)
{
    gtk_window_close(GTK_WINDOW(self->ctrl_window));
}

void my_titlebar_set_window(MyTitleBar *self, GtkWidget *window)
{
    gtk_window_set_titlebar(GTK_WINDOW(window), self->header);
    self->ctrl_window = window;
}

static void my_titlebar_init(MyTitleBar *self)
{
    // Create widgets
    self->header = gtk_header_bar_new();
    gtk_widget_set_css_classes(self->header, NULL);
    gtk_widget_add_css_class(self->header, "mytitlebar");

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
    gtk_css_provider_load_from_resource(provider, "/org/gtk/daleclack/title_style.css");
    gtk_style_context_add_provider_for_display(gtk_widget_get_display(GTK_WIDGET(self->header)),
                                               GTK_STYLE_PROVIDER(provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_signal_connect_swapped(self->btn_close, "clicked", G_CALLBACK(ctrl_win_close), self);
    g_signal_connect_swapped(self->btn_mini, "clicked", G_CALLBACK(ctrl_win_hide), self);
}

static void my_titlebar_class_init(MyTitleBarClass *klass)
{
}

MyTitleBar *my_titlebar_new()
{
    return My_TitleBar(g_object_new(my_titlebar_get_type(), NULL));
}
