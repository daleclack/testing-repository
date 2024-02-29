#include "jsonfile.h"
#include "ScoresWin.h"
#include "ScoresItem.h"
#include <fstream>

struct _ScoresWin
{
    GtkWindow parent;
    // Child widgets
    GtkWidget *scrolled_win;
    GtkWidget *main_box;
    GtkWidget *btn_close;

    // List widgets
    GtkWidget *list_view;
    GtkSingleSelection *selection;
    GtkListItemFactory *factory_name, *factory_time;
    GtkColumnViewColumn *column_name, *column_time;
    GListStore *store;
};

G_DEFINE_TYPE(ScoresWin, scores_win, GTK_TYPE_WINDOW)

static gboolean scores_win_closed(GtkWidget *window, ScoresWin *self)
{
    gtk_widget_set_visible(window, FALSE);
    return TRUE;
}

static void btnclose_clicked(GtkButton *btn, GtkWindow *self)
{
    gtk_window_close(self);
}

static void name_factory_setup(GtkSignalListItemFactory *factory,
                               GtkListItem *item)
{
    GtkWidget *label = gtk_label_new("");
    gtk_list_item_set_child(item, label);
}

static void name_factory_bind(GtkListItemFactory *factory,
                              GtkListItem *item)
{
    // Get child
    GtkWidget *label;
    label = gtk_list_item_get_child(item);

    // Get Item
    ScoresItem *item1 = Scores_Item(gtk_list_item_get_item(item));
    gtk_label_set_label(GTK_LABEL(label),
                        scores_item_get_name(item1));
}

static void time_factory_setup(GtkSignalListItemFactory *factory,
                               GtkListItem *item)
{
    GtkWidget *label = gtk_label_new("");
    gtk_list_item_set_child(item, label);
}

static void time_factory_bind(GtkListItemFactory *factory,
                              GtkListItem *item)
{
    // Get child
    GtkWidget *label;
    label = gtk_list_item_get_child(item);

    // Get Item
    ScoresItem *item1 = Scores_Item(gtk_list_item_get_item(item));
    char *time_str = g_strdup_printf("%d", scores_item_get_time(item1));
    gtk_label_set_label(GTK_LABEL(label), time_str);
}

static gint sort_func(gpointer a, gpointer b, gpointer user_data)
{
    ScoresItem *item_a = Scores_Item(a);
    ScoresItem *item_b = Scores_Item(b);
    int time_a = scores_item_get_time(item_a);
    int time_b = scores_item_get_time(item_b);

    // Return result
    if (time_a > time_b)
    {
        return 1;
    }

    if (time_a == time_b)
    {
        return 0;
    }

    if (time_a < time_b)
    {
        return -1;
    }
    return 0;
}

static void scores_win_init(ScoresWin *self)
{
    // Initalize window
    gtk_window_set_title(GTK_WINDOW(self), "Scores");
    gtk_window_set_icon_name(GTK_WINDOW(self), "org.gtk.daleclack");

    // Create widgets
    self->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->scrolled_win = gtk_scrolled_window_new();
    self->btn_close = gtk_button_new_with_label("Close");
    g_signal_connect(self->btn_close, "clicked", G_CALLBACK(btnclose_clicked), self);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(self->scrolled_win),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(self->scrolled_win, 300, 400);
    gtk_widget_set_halign(self->btn_close, GTK_ALIGN_CENTER);

    // Create store
    self->store = g_list_store_new(scores_item_get_type());
    self->selection = gtk_single_selection_new(G_LIST_MODEL(self->store));

    // Create Column View
    self->list_view = gtk_column_view_new(GTK_SELECTION_MODEL(self->selection));

    // Create factory for name
    self->factory_name = gtk_signal_list_item_factory_new();
    g_signal_connect(self->factory_name, "bind", G_CALLBACK(name_factory_bind), NULL);
    g_signal_connect(self->factory_name, "setup", G_CALLBACK(name_factory_setup), NULL);
    self->column_name = gtk_column_view_column_new("Name", self->factory_name);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(self->list_view), self->column_name);

    // Create factory for time
    self->factory_time = gtk_signal_list_item_factory_new();
    g_signal_connect(self->factory_time, "bind", G_CALLBACK(time_factory_bind), NULL);
    g_signal_connect(self->factory_time, "setup", G_CALLBACK(time_factory_setup), NULL);
    self->column_time = gtk_column_view_column_new("Time", self->factory_time);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(self->list_view), self->column_time);

    // Pack widgets
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(self->scrolled_win), self->list_view);
    gtk_box_append(GTK_BOX(self->main_box), self->scrolled_win);
    gtk_box_append(GTK_BOX(self->main_box), self->btn_close);
    gtk_window_set_child(GTK_WINDOW(self), self->main_box);
}

static void scores_win_class_init(ScoresWinClass *klass)
{
}

ScoresWin *scores_win_new(GtkWindow *parent)
{
    return Scores_Win(g_object_new(scores_win_get_type(),
                                   "transient-for", parent, NULL));
}

void scores_win_update_and_show(ScoresWin *self)
{
    std::fstream infile;
    infile.open("scores.json", std::ios_base::in);

    if (infile.is_open())
    {
        // Read data from json file
        json data = json::parse(infile);
        std::vector<std::string> name_vec = data["name"];
        std::vector<int> time_vec = data["time"];

        // Clear the store
        g_list_store_remove_all(self->store);

        // Append data to the store
        for (int i = 0; i < name_vec.size(); i++)
        {
            g_list_store_append(self->store,
                                scores_item_new(name_vec[i].c_str(), time_vec[i]));
        }
        g_list_store_sort(self->store, (GCompareDataFunc)sort_func, NULL);
    }
    gtk_window_present(GTK_WINDOW(self));
}
