#include "MainWin.h"
#include "TestWin.h"

struct _MainWin
{
    GtkApplicationWindow parent_instance;
    GtkWidget *main_box, *btn_box;
    GtkWidget *btn_test;
    GtkWidget *label_space;
    TestWin *test_win;
};

G_DEFINE_TYPE(MainWin, main_win, GTK_TYPE_APPLICATION_WINDOW)

static void btntest_clicked(GtkWidget *btn, MainWin *self)
{
    gboolean test_win_showed = gtk_widget_get_visible(GTK_WIDGET(self->test_win));
    if (test_win_showed)
    {
        gtk_widget_set_visible(GTK_WIDGET(self->test_win), FALSE);
    }
    else
    {
        gtk_widget_set_visible(GTK_WIDGET(self->test_win), TRUE);
        gtk_window_present(GTK_WINDOW(self->test_win));
    }
}

static void main_win_init(MainWin *self)
{
    // Initalize window
    gtk_window_set_default_size(GTK_WINDOW(self), 800, 450);
    gtk_window_set_default_icon_name("org.gtk.daleclack");
    gtk_window_set_title(GTK_WINDOW(self), "Wayland window test");

    // Create child window
    self->test_win = test_win_new(GTK_WINDOW(self));
    gtk_widget_set_visible(GTK_WIDGET(self->test_win), FALSE);

    // Create Box and buttons
    self->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    self->btn_test = gtk_button_new_with_label("Test");
    self->label_space = gtk_label_new(" ");
    g_signal_connect(self->btn_test, "clicked", G_CALLBACK(btntest_clicked), self);

    // Pack widgets
    gtk_widget_set_hexpand(self->label_space, TRUE);
    gtk_widget_set_vexpand(self->label_space, TRUE);
    gtk_widget_set_halign(self->btn_test, GTK_ALIGN_START);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_test);
    gtk_box_append(GTK_BOX(self->main_box), self->label_space);
    gtk_box_append(GTK_BOX(self->main_box), self->btn_box);
    gtk_window_set_child(GTK_WINDOW(self), self->main_box);
}

static void main_win_class_init(MainWinClass *self)
{
}

MainWin *main_win_new(GtkApplication *app)
{
    return Main_Win(g_object_new(main_win_get_type(),
                                 "application", app, NULL));
}