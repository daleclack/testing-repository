#include "MainWin.h"
#include "MyItem.h"

struct _MainWin{
    GtkApplicationWindow parent_instance;
    GListModel *model;
    GtkWidget *view;
    GtkListItemFactory *factory;
    GtkSingleSelection *selection;
};

G_DEFINE_TYPE(MainWin, main_win, GTK_TYPE_APPLICATION_WINDOW)

static void setup_list_item(GtkListItemFactory *factory, GtkListItem *item){
    // Create label to show list item
    GtkWidget *label;
    label = gtk_label_new(" ");
    gtk_list_item_set_child(item, label);
}

static void bind_list_item(GtkListItemFactory *factory, GtkListItem *item){
    // Get child for list item
    GtkWidget *label;
    label = gtk_list_item_get_child(item);

    // Get string
    MyItem *item1 = (MyItem*)gtk_list_item_get_item(item);
    GString *string = my_item_get_string(item1);
    gtk_label_set_label(GTK_LABEL(label), string->str);
    // g_string_free(string, TRUE);
}

static GListModel *create_list_model()
{
    GListStore *store;

    // Create the list store
    store = g_list_store_new(my_item_get_type());

    // Fill the store
    g_list_store_append(store, my_item_new("Item 1"));
    g_list_store_append(store, my_item_new("Item 2"));
    g_list_store_append(store, my_item_new("Item 3"));

    return G_LIST_MODEL(store);
}

static void main_win_dispose(GObject *object){
    // Clear List Model
    G_OBJECT_CLASS(main_win_parent_class)->dispose(object);
}

static void main_win_init(MainWin *self){
    // Initalize window
    gtk_window_set_icon_name(GTK_WINDOW(self), "org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(self), 640, 360);

    // Create list model
    self->model = create_list_model();

    // Create Factory
    self->factory = gtk_signal_list_item_factory_new();
    g_signal_connect(self->factory, "setup", G_CALLBACK(setup_list_item), NULL);
    g_signal_connect(self->factory, "bind", G_CALLBACK(bind_list_item), NULL);

    // Create view
    self->selection = gtk_single_selection_new(self->model);
    self->view = gtk_list_view_new(GTK_SELECTION_MODEL(self->selection), self->factory);
    gtk_window_set_child(GTK_WINDOW(self), self->view);
}

static void main_win_class_init(MainWinClass *klass){
    G_OBJECT_CLASS(klass)->dispose = main_win_dispose;
}

MainWin *main_win_new(GtkApplication *app){
    return MAIN_WIN(g_object_new(main_win_get_type(), "application", app, NULL));
}
