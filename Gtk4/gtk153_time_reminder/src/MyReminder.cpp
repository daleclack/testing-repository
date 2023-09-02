#include "MyReminder.h"
#include <fstream>
#include "timer.h"

struct _MyReminder
{
    GtkApplicationWindow parent_instance;
    GtkWidget *time_label;
    int year, month, day;
    std::string color;
};

G_DEFINE_TYPE(MyReminder, my_reminder, GTK_TYPE_APPLICATION_WINDOW)

static void load_json_data(MyReminder *self)
{
    std::fstream json_file;
    json json_data;
    std::string default_color("blue");

    // Open json file for data
    json_file.open("config.json", std::ios_base::in);

    // Load json data
    if (json_file.is_open())
    {
        json_data = json::parse(json_file);
    }
    else
    {
        // Json file not exist, load default config
        self->color = default_color;
        self->year = 2023;
        self->month = 12;
        self->day = 23;
    }

    if (!json_data.empty()){
        // Get json data
        std::string tmp_color = json_data["color_set"];
        self->color = tmp_color;
        self->year = json_data["year"];
        self->month = json_data["month"];
        self->day = json_data["day"];
    }
    else
    {
        // No json data, load default config
        self->color = default_color;
        self->year = 2023;
        self->month = 12;
        self->day = 23;
    }
}

static void my_reminder_init(MyReminder *self)
{
    // Set properties of window
    gtk_window_set_icon_name(GTK_WINDOW(self), "org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(self), 240, 200);
    gtk_window_set_title(GTK_WINDOW(self), "Reminder");

    // Load data from json file
    load_json_data(self);

    // Create and add a label
    self->time_label = gtk_label_new(" ");

    // Get time duration
    char time_str[57];
    int time = get_time_duration(self->year, self->month, self->day);
    if (time >= 0)
    {
        snprintf(time_str, sizeof(time_str),
                 "<span foreground=\"%s\" size='16pt'>%d</span>\nDays Left", 
                 self->color.c_str(), time);
    }
    else
    {
        strncpy(time_str, "<span foreground=\"red\" size='16pt'>Time is out!</span>", 56);
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
