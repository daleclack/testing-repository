#include "MyPrefs.h"

struct _MyPrefs
{
    GtkWindow parent_instance;
    GtkBuilder *prefs_builder;
    GtkWidget *background;
};

G_DEFINE_TYPE(MyPrefs, my_prefs, GTK_TYPE_WINDOW)

static void my_prefs_init(MyPrefs *self) {}

static void my_prefs_class_init(MyPrefsClass *klass)
{
}

GtkWidget *my_prefs_new(GtkWidget *back, GtkWindow *parent)
{
    GtkWidget *prefs_win = GTK_WIDGET(g_object_new(my_prefs_get_type(),
                                                   "transient-for", parent, NULL));
    MY_PREFS(prefs_win)->background = back;
    return prefs_win;
}
