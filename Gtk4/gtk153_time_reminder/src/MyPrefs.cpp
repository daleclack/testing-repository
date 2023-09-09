#include "MyReminder.h"
#include "MyPrefs.h"
#include "config.h"
#include <fstream>

struct _MyPrefs
{
    GtkWindow parent_instance;
    GtkWidget *main_box, *btn_box;
    GtkWidget *label_color;
    GtkWidget *calendar_frame, *calendar;
    GtkWidget *color_button;
    GtkWidget *btnapply;
    GtkColorDialog *dialog;
    GtkWidget *color_drop;
};

G_DEFINE_TYPE(MyPrefs, my_prefs, GTK_TYPE_WINDOW)

static void load_reminder_config(MyPrefs *prefs)
{
    // Open file for json config
    std::fstream infile;
    infile.open("config.json", std::ios_base::in);
    json json_data;
    GDateTime *selected_day;

    if (infile.is_open())
    {
        json_data = json::parse(infile);
    }
    else
    {
        // Select Default Date
        GTimeZone *timezone = g_time_zone_new_local();
        selected_day = g_date_time_new(timezone, default_year,
                                       default_month, default_day, 8, 0, 0);
        gtk_calendar_select_day(GTK_CALENDAR(prefs->calendar), selected_day);
        return;
    }

    if (!json_data.empty())
    {
        // Get date from json data
        int year = json_data["year"];
        int month = json_data["month"];
        int day = json_data["day"];

        // Select Day
        GTimeZone *timezone = g_time_zone_new_local();
        selected_day = g_date_time_new(timezone, year,
                                       month, day, 8, 0, 0);
        gtk_calendar_select_day(GTK_CALENDAR(prefs->calendar), selected_day);
    }
    else
    {
        // Select Default Date
        GTimeZone *timezone = g_time_zone_new_local();
        selected_day = g_date_time_new(timezone, default_year,
                                       default_month, default_day, 8, 0, 0);
        gtk_calendar_select_day(GTK_CALENDAR(prefs->calendar), selected_day);
    }
}

static void btnapply_clicked(GtkWidget *widget, MyPrefs *prefs)
{
    // Get Selected year,month and day
    GDateTime *selected_day;
    selected_day = gtk_calendar_get_date(GTK_CALENDAR(prefs->calendar));

    int year1, month1, day1;
    year1 = g_date_time_get_year(selected_day);
    month1 = g_date_time_get_month(selected_day);
    day1 = g_date_time_get_day_of_month(selected_day);

    // Create json data
    json out_data = json::parse(R"(
        {
            "color_set":"blue",
            "year":2023,
            "month":12,
            "day":23
        }
    )");
    out_data["year"] = year1;
    out_data["month"] = month1;
    out_data["day"] = day1;

    // Save data to the json file
    std::fstream outfile;
    outfile.open("config.json", std::ios_base::out);

    // Save data to the file when available
    if (outfile.is_open())
    {
        outfile<<out_data;
    }
    outfile.close();
}

static void my_prefs_init(MyPrefs *self)
{
    // Initalize preferneces window
    // gtk_window_set_icon_name(GTK_WINDOW(self), "org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(self), 300, 200);

    // Create layout and widgets
    self->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    self->calendar_frame = gtk_frame_new("Select a date For reminder");
    gtk_widget_set_halign(self->main_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(self->main_box, GTK_ALIGN_CENTER);

    // Create calendar and add it to the frame
    self->calendar = gtk_calendar_new();
    gtk_frame_set_child(GTK_FRAME(self->calendar_frame), self->calendar);
    gtk_box_append(GTK_BOX(self->main_box), self->calendar_frame);

    // Load config
    load_reminder_config(self);

    // Create information labels
    self->label_color = gtk_label_new("Font Color:");
    gtk_box_append(GTK_BOX(self->btn_box), self->label_color);

    // Create color widgets
    self->dialog = gtk_color_dialog_new();
    self->color_button = gtk_color_dialog_button_new(self->dialog);
    gtk_box_append(GTK_BOX(self->btn_box), self->color_button);
    gtk_widget_set_halign(self->btn_box, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(self->main_box), self->btn_box);

    // Add button to the main box
    self->btnapply = gtk_button_new_with_label("Apply Settings");
    g_signal_connect(self->btnapply, "clicked", G_CALLBACK(btnapply_clicked), self);
    gtk_widget_set_halign(self->btnapply, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(self->main_box), self->btnapply);

    // Set margin
    gtk_widget_set_margin_bottom(self->main_box, 10);
    gtk_widget_set_margin_end(self->main_box, 10);
    gtk_widget_set_margin_start(self->main_box, 10);
    gtk_widget_set_margin_top(self->main_box, 10);
    gtk_window_set_child(GTK_WINDOW(self), self->main_box);
}

static void my_prefs_class_init(MyPrefsClass *klass)
{
}

MyPrefs *my_prefs_new(GtkWindow *parent)
{
    return MY_PREFS(g_object_new(my_prefs_get_type(),
                                 "transient-for", parent, NULL));
}