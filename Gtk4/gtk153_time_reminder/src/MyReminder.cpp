#include "MyReminder.h"
#include <fstream>
#include "timer.h"
#include "MyPrefs.h"
#include "config.h"

struct _MyReminder
{
    GtkApplicationWindow parent_instance;
    GtkWidget *time_label;
    GtkWidget *header, *btn_prefs;
    int year, month, day;
    std::string color;
};

G_DEFINE_TYPE(MyReminder, my_reminder, GTK_TYPE_APPLICATION_WINDOW)

static void load_json_data(MyReminder *self)
{
    std::fstream json_file;
    json json_data;
    std::string color_string(default_color);

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
        self->color = color_string;
        self->year = default_year;
        self->month = default_month;
        self->day = default_day;
        return;
    }

    if (!json_data.empty())
    {
        // Get json data
        color_string = json_data["color_set"];
        self->color = color_string;
        self->year = json_data["year"];
        self->month = json_data["month"];
        self->day = json_data["day"];
    }
    else
    {
        // No json data, load default config
        self->color = color_string;
        self->year = default_year;
        self->month = default_month;
        self->day = default_day;
    }
}

static void btnprefs_clicked(GtkWidget *widget, MyReminder *win)
{
    // Show the preference window
    // Create Preference window
    MyPrefs *prefs_window = my_prefs_new(GTK_WINDOW(win));
    gtk_window_present(GTK_WINDOW(prefs_window));
}

static void my_reminder_init(MyReminder *self)
{
    // Set properties of window
    gtk_window_set_icon_name(GTK_WINDOW(self), "org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(self), 350, 250);
    gtk_window_set_title(GTK_WINDOW(self), "Reminder");
    
    // Create header bar
    self->header = gtk_header_bar_new();
    gtk_header_bar_set_decoration_layout(GTK_HEADER_BAR(self->header),
        "close,minimize,maximize:menu");
    gtk_window_set_titlebar(GTK_WINDOW(self), self->header);

    // Create button for preference
    self->btn_prefs = gtk_button_new_with_label("Prefs");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(self->header), self->btn_prefs);
    g_signal_connect(self->btn_prefs, "clicked", G_CALLBACK(btnprefs_clicked), self);

    // Load data from json file
    load_json_data(self);

    // Create and add a label
    self->time_label = gtk_label_new(" ");

    // Get time duration
    char time_str[label_max_length];

    // String for timeout
    const char *timeout_str = "<span foreground=\"red\" size='16pt'>Time is out!</span>";

    // Get days for deadline
    int time = get_time_duration(self->year, self->month, self->day);
    if (time >= 0)
    {
        snprintf(time_str, sizeof(time_str),
                 "<span foreground=\"%s\" size='16pt'>%d</span>\nDays Left",
                 self->color.c_str(), time);
    }
    else
    {
        strncpy(time_str, timeout_str, strlen(timeout_str));
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
