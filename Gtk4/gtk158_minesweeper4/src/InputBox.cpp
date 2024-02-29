#include <vector>
#include <string>
#include <fstream>
#include "InputBox.h"
#include "jsonfile.h"

struct _InputBox
{
    GtkWindow parent_instance;
    GtkWidget *main_box, *btn_box;
    GtkWidget *entry_name;
    GtkWidget *scores_check;
    GtkWidget *btn_ok, *btn_cancel;
    int game_time;
};

G_DEFINE_TYPE(InputBox, input_box, GTK_TYPE_WINDOW)

static std::vector<std::string> names;
static std::vector<int> times;
static json data;

static void btnok_clicked(GtkButton *btn, InputBox *self)
{
    // Save score to json file
    // Open a file to save json data
    std::fstream outfile;
    outfile.open("scores.json", std::ios_base::out);
    if (outfile.is_open())
    {
        // Insert data to json
        const char *c_name = gtk_editable_get_text(GTK_EDITABLE(self->entry_name));
        std::string name = std::string(c_name);
        names.push_back(name);
        times.push_back(self->game_time);
        data["name"] = names;
        data["time"] = times;

        // Output data
        outfile << data;
    }
    outfile.close();

    // Show Scores window

    gtk_window_close(GTK_WINDOW(self));
}

static gboolean input_box_closed(GtkWidget *win, InputBox *self)
{
    // Hide the window
    gtk_widget_set_visible(win, FALSE);
    return TRUE;
}

static void input_box_init(InputBox *self)
{
    // Initalize window
    gtk_window_set_default_size(GTK_WINDOW(self), 300, 150);

    // Create widgets
    self->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    self->entry_name = gtk_entry_new();
    self->scores_check = gtk_check_button_new_with_label("Show scores window");
    self->btn_ok = gtk_button_new_with_label("OK");
    self->btn_cancel = gtk_button_new_with_label("Cancel");

    // Link signals
    g_signal_connect(self->btn_ok, "clicked", G_CALLBACK(btnok_clicked), self);
    g_signal_connect(self, "close-request", G_CALLBACK(input_box_closed), self);
    g_signal_connect_swapped(self->btn_cancel, "clicked", G_CALLBACK(gtk_window_close), self);

    // Pack widgets
    gtk_box_append(GTK_BOX(self->main_box), self->entry_name);
    gtk_box_append(GTK_BOX(self->main_box), self->scores_check);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_ok);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_cancel);
    gtk_box_append(GTK_BOX(self->main_box), self->btn_box);
    gtk_widget_set_margin_bottom(self->main_box, 10);
    gtk_widget_set_margin_end(self->main_box, 10);
    gtk_widget_set_margin_start(self->main_box, 10);
    gtk_widget_set_margin_top(self->main_box, 10);
    gtk_widget_set_halign(self->btn_box, GTK_ALIGN_END);
    // gtk_widget_set_halign(self->main_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(self->main_box, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(self), self->main_box);
}

static void input_box_class_init(InputBoxClass *klass)
{
}

InputBox *input_box_new(GtkWindow *parent)
{
    return Input_Box(g_object_new(input_box_get_type(),
                                  "transient-for", parent, NULL));
}

void input_box_present(InputBox *self)
{
    // Show the input box
    gtk_window_present(GTK_WINDOW(self));
}

void input_box_set_game_time(InputBox *self, int time)
{
    // Try to open json file
    std::fstream jsonfile;
    jsonfile.open("scores.json", std::ios_base::in);

    // If json file opened, read the data
    if (jsonfile.is_open())
    {
        data = json::parse(jsonfile);
        std::vector<std::string> names1 = data["name"];
        std::vector<int> times1 = data["time"];
        names = names1;
        times = times1;
    }
    else
    {
        // Otherwist, create json data
        data = json::parse(R"(
            {
                "name":[" "],
                "time":[0]
            }
        )");
    }
    jsonfile.close();

    // Set game time for input box
    self->game_time = time;
}
