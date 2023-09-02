#include "MyPrefs.h"

struct _MyPrefs
{
    GtkWindow parent_instance;
};

G_DEFINE_TYPE(MyPrefs, my_prefs, GTK_TYPE_WINDOW)

static void my_prefs_init(MyPrefs *self)
{}

static void my_prefs_class_init(MyPrefsClass *klass)
{}