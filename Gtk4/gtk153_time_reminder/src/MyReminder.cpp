#include "MyReminder.h"
#include "timer.h"

struct _MyReminder
{
    GtkApplicationWindow parent_instance;
    GtkWidget *time_label;
};

G_DEFINE_TYPE(MyReminder, my_reminder, GTK_TYPE_APPLICATION_WINDOW)

static void my_reminder_init(MyReminder *self)
{
    // Set properties of window
    gtk_window_set_icon_name(GTK_WINDOW(self), "org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(self), 240, 200);
    gtk_window_set_title(GTK_WINDOW(self), "Reminder");

    // Create and add a label
    self->time_label = gtk_label_new(" ");

    // Get time duration
    char time_str[57];
    int time = get_time_duration(2023, 12, 23);
    if(time >= 0){
        snprintf(time_str, sizeof(time_str), "<span foreground=\"blue\" size='16pt'>%d</span>\nDays Left", time);
    }else{
        strncpy(time_str, "<span foreground=\"blue\" size='16pt'>Time is out!</span>", 13);
    }
    
    // Text style of the label
    gtk_label_set_markup(GTK_LABEL(self->time_label), time_str);
    gtk_label_set_use_markup(GTK_LABEL(self->time_label), TRUE);

    // // Set label
    // gtk_label_set_label(GTK_LABEL(self->time_label), time_str);

    gtk_window_set_child(GTK_WINDOW(self), self->time_label);
}

static void my_reminder_class_init(MyReminderClass *klass)
{
}

MyReminder *my_reminder_new(GtkApplication *app)
{
    return MY_REMINDER(g_object_new(my_reminder_get_type(),
                                    "application", app, NULL));
}
