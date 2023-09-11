#include "MyReminder.h"
#include "MyPrefs.h"
#include "config.h"
#include "MyMsgBox.h"
#include <fstream>
#include <string>

struct _MyPrefs
{
    GtkWindow parent_instance;
    GtkWidget *main_box, *color_box;
    GtkWidget *label_color;
    GtkWidget *calendar_frame, *calendar;
    GtkWidget *color_button;
    GtkWidget *btnapply;
    GtkColorDialog *dialog;
    char color[12];
    GtkWidget *color_drop;
    GtkWidget *check_default_color, *check_rgba_color;
    GtkWidget *def_color_box, *rgba_color_box;
};

G_DEFINE_TYPE(MyPrefs, my_prefs, GTK_TYPE_WINDOW)

static const char *color_strings[] =
    {
        "aqua",
        "black",
        "blue",
        "fuchsia",
        "gray",
        "green",
        "lime",
        "maroon",
        "navy",
        "olive",
        "purple",
        "red",
        "silver",
        "teal",
        "white",
        "yellow",
        NULL};

// Convert 2-bit 16numbers to 0-1 float for rgba
static float str16_to_rgb_float(char high_bit, char low_bit)
{
    int rgba_255 = 0;
    if (high_bit >= 'A')
    {
        rgba_255 += (high_bit - 'A' + 10) * 16;
    }
    else
    {
        rgba_255 += (high_bit - '0') * 16;
    }

    if (low_bit >= 'A')
    {
        rgba_255 += (low_bit - 'A' + 10);
    }
    else
    {
        rgba_255 += (low_bit - '0');
    }
    return rgba_255 / 255.0;
}

static void load_color(MyPrefs *prefs, std::string &color_str1)
{
    if (color_str1[0] == '#')
    {
        // RGBA Color config
        gtk_check_button_set_active(GTK_CHECK_BUTTON(prefs->check_rgba_color),
                                    TRUE);

        // Get color setting from color string
        GdkRGBA rgba_color;
        float red, green, blue, alpha;
        red = str16_to_rgb_float(color_str1[1], color_str1[2]);
        green = str16_to_rgb_float(color_str1[3], color_str1[4]);
        blue = str16_to_rgb_float(color_str1[5], color_str1[6]);
        alpha = str16_to_rgb_float(color_str1[7], color_str1[8]);
        rgba_color.alpha = alpha;
        rgba_color.blue = blue;
        rgba_color.red = red;
        rgba_color.green = green;

        // Set rgba color for color button
        gtk_color_dialog_button_set_rgba(
            GTK_COLOR_DIALOG_BUTTON(prefs->color_button), &rgba_color);
    }
    else
    {
        // Default Color config
        gtk_check_button_set_active(GTK_CHECK_BUTTON(prefs->check_default_color),
                                    TRUE);
        for (int i = 0; color_strings[i] != NULL; i++)
        {
            const char *color_set_str = color_strings[i];
            if (strncmp(color_set_str,
                        color_str1.c_str(),
                        strlen(color_set_str)) == 0)
            {
                gtk_drop_down_set_selected(GTK_DROP_DOWN(prefs->color_drop), i);
            }
        }
    }
}

static void load_reminder_config(MyPrefs *prefs)
{
    // Open file for json config
    std::fstream infile;
    infile.open("config.json", std::ios_base::in);
    json json_data;
    GDateTime *selected_day;
    std::string color_str(default_color);

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

        // Get Color string
        color_str = json_data["color_set"];

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
    // Load color config
    load_color(prefs, color_str);
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

    // Get color config
    std::string color_string1;
    if (gtk_check_button_get_active(
            GTK_CHECK_BUTTON(prefs->check_default_color)))
    {
        guint index = gtk_drop_down_get_selected(GTK_DROP_DOWN(prefs->color_drop));
        color_string1.append(color_strings[index]);
    }
    else
    {
        // Get GdkRGBA object for color
        const GdkRGBA *rgba_color;
        rgba_color = gtk_color_dialog_button_get_rgba(
            GTK_COLOR_DIALOG_BUTTON(prefs->color_button));

        // Convert color from (0,1) to (0,255)
        int red = (rgba_color->red) * 255;
        int green = (rgba_color->green) * 255;
        int blue = (rgba_color->blue) * 255;
        int alpha = (rgba_color->alpha) * 255;

        // Format the color string to #XXXXXXXX
        snprintf(prefs->color, 12, "#%02X%02X%02X%02X", red,
                 green, blue, alpha);
        color_string1.append(prefs->color);
    }

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
    out_data["color_set"] = color_string1;

    // Save data to the json file
    std::fstream outfile;
    outfile.open("config.json", std::ios_base::out);

    // Save data to the file when available
    if (outfile.is_open())
    {
        // OutPut the file data
        outfile << out_data;

        // Show a message box
        MyMsgBox *msgbox = my_msgbox_new(GTK_WINDOW(prefs));
        my_msgbox_show(msgbox, "Config File Saved!\nRestart to take affect");
    }
    outfile.close();
}

static void my_prefs_init(MyPrefs *self)
{
    // Initalize preferneces window
    // gtk_window_set_icon_name(GTK_WINDOW(self), "org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(self), 300, 200);
    gtk_window_set_title(GTK_WINDOW(self), "Preferences");

    // Create layout and widgets
    self->main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    self->color_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->def_color_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->rgba_color_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->calendar_frame = gtk_frame_new("Select a date For reminder");
    gtk_widget_set_halign(self->main_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(self->main_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(self->color_box, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(self->def_color_box, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(self->rgba_color_box, GTK_ALIGN_CENTER);

    // Create calendar and add it to the frame
    self->calendar = gtk_calendar_new();
    gtk_frame_set_child(GTK_FRAME(self->calendar_frame), self->calendar);
    gtk_box_append(GTK_BOX(self->main_box), self->calendar_frame);

    // Create information labels
    self->label_color = gtk_label_new("Font Color:");
    gtk_widget_set_halign(self->label_color, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(self->color_box), self->label_color);

    // Create check buttons for selection
    self->check_default_color = gtk_check_button_new_with_label("Use default color");
    self->check_rgba_color = gtk_check_button_new_with_label("Use color from RGBA");
    gtk_check_button_set_group(GTK_CHECK_BUTTON(self->check_default_color),
                               GTK_CHECK_BUTTON(self->check_rgba_color));
    gtk_check_button_set_active(GTK_CHECK_BUTTON(self->check_default_color), TRUE);

    // Create defaut colors dropdown
    self->color_drop = gtk_drop_down_new_from_strings(color_strings);
    gtk_drop_down_set_selected(GTK_DROP_DOWN(self->color_drop), 2);
    gtk_box_append(GTK_BOX(self->def_color_box), self->check_default_color);
    gtk_box_append(GTK_BOX(self->def_color_box), self->color_drop);
    gtk_box_append(GTK_BOX(self->color_box), self->def_color_box);

    // Create widgets for rgba color
    self->dialog = gtk_color_dialog_new();
    self->color_button = gtk_color_dialog_button_new(self->dialog);
    gtk_box_append(GTK_BOX(self->rgba_color_box), self->check_rgba_color);
    gtk_box_append(GTK_BOX(self->rgba_color_box), self->color_button);
    gtk_box_append(GTK_BOX(self->color_box), self->rgba_color_box);

    // Add button to the main box
    self->btnapply = gtk_button_new_with_label("Apply Settings");
    g_signal_connect(self->btnapply, "clicked", G_CALLBACK(btnapply_clicked), self);
    gtk_widget_set_halign(self->btnapply, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(self->color_box), self->btnapply);
    gtk_box_append(GTK_BOX(self->main_box), self->color_box);

    // Bind properties of objects
    g_object_bind_property(self->check_default_color, "active",
                           self->color_drop, "sensitive",
                           G_BINDING_DEFAULT);
    g_object_bind_property(self->check_rgba_color, "active",
                           self->color_button, "sensitive",
                           G_BINDING_DEFAULT);
    // The color button should disabled defaultly
    gtk_widget_set_sensitive(self->color_button, FALSE);

    // Load config
    load_reminder_config(self);

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
