#include "MyTitleBar.h"

struct _MyTitleBar{
    GObject parent_instance;
    GtkWindow *ctrl_window;
    GtkWidget *header;
    GtkWidget *btn_close, *btn_mini;
};

G_DEFINE_TYPE(MyTitleBar, my_titlebar, G_TYPE_OBJECT)

static void my_titlebar_init(MyTitleBar *self)
{

}

static void my_titlebar_class_init(MyTitleBarClass *klass)
{

}
