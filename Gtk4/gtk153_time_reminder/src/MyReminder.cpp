#include "MyReminder.h"

struct _MyReminder
{
    GtkApplicationWindow parent_instance;
    GtkLabel *label1;
};

G_DEFINE_TYPE(MyReminder, my_reminder, GTK_TYPE_APPLICATION_WINDOW)

static void my_reminder_init(MyReminder *self)
{
    
}

static void my_reminder_class_init(MyReminderClass *klass)
{
}

MyReminder *my_reminder_new(GtkApplication *app)
{
    return MY_REMINDER(g_object_new(my_reminder_get_type(),
                                    "application", app, NULL));
}
