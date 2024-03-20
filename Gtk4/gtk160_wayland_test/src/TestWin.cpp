#include "TestWin.h"
#include "MyTitleBar.h"

struct _TestWin
{
    GtkWindow parent_instance;
    MyTitleBar *header;
};

G_DEFINE_TYPE(TestWin, test_win, GTK_TYPE_WINDOW)

static void test_win_closed(GtkWindow *win, TestWin *self)
{
    g_print("window closed!\n");
}

static void test_win_init(TestWin *self)
{
    // Initalize window
    gtk_window_set_title(GTK_WINDOW(self), "Test Window 1");
    gtk_window_set_hide_on_close(GTK_WINDOW(self), TRUE);

    // Add a custom headerbar
    self->header = my_titlebar_new();
    my_titlebar_set_window(self->header, GTK_WIDGET(self));

    g_signal_connect(self, "close-request", G_CALLBACK(test_win_closed), self);
}

static void test_win_class_init(TestWinClass *klass)
{
}

TestWin *test_win_new(GtkWindow *parent)
{
    return Test_Win(g_object_new(test_win_get_type(),
                                 "transient-for", parent, NULL));
}
