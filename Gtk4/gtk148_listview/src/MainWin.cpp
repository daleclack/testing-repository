#include "MainWin.h"
#include "MyItem.h"

struct _MainWin
{
    GtkApplicationWindow parent_instance;
    GListModel *model;
    GtkWidget *view;
    GtkListItemFactory *factory;
    GtkSingleSelection *selection;
    GtkWidget *main_box;
    GtkWidget *scrolled_window;
    GtkWidget *btn_add, *btn_remove, *btn_remove_all;
    GtkWidget *entry_add;
};

G_DEFINE_TYPE(MainWin, main_win, GTK_TYPE_APPLICATION_WINDOW)

static void setup_list_item(GtkListItemFactory *factory, GtkListItem *item)
{
    // Create label to show list item
    GtkWidget *label;
    label = gtk_label_new(" ");
    gtk_list_item_set_child(item, label);
}

static void bind_list_item(GtkListItemFactory *factory, GtkListItem *item)
{
    // Get child for list item
    GtkWidget *label;
    label = gtk_list_item_get_child(item);

    // Get string
    MyItem *item1 = (MyItem *)gtk_list_item_get_item(item);
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

static void btnadd_clicked(GtkWidget *widget, MainWin *win)
{
    // Add a item to the store
    GListModel *model = win->model;
    GtkWidget *entry = win->entry_add;

    // Get text to add
    const gchar *str = gtk_editable_get_text(GTK_EDITABLE(entry));

    // Add item to store
    g_list_store_append(G_LIST_STORE(model), my_item_new(str));
}

static void btnremove_clicked(GtkWidget *widget, MainWin *win)
{
    // Get the position of selected item
    GtkSingleSelection *selection = win->selection;
    guint position = gtk_single_selection_get_selected(selection);

    // Remove selected item
    GListStore *store = G_LIST_STORE(win->model);
    g_list_store_remove(store, position);
}

static void btnremove_all_clicked(GtkWidget *widget, MainWin *win)
{
    // Remove all data from store
    GListModel *model = win->model;
    g_list_store_remove_all(G_LIST_STORE(model));
}

static void selection_changed(GtkSelectionModel *model,
                              guint position,
                              guint n_data,
                              MainWin *win)
{
    
}

static void main_win_dispose(GObject *object)
{
    // Clear List Model
    g_list_store_remove_all(G_LIST_STORE(MAIN_WIN(object)->model));
    G_OBJECT_CLASS(main_win_parent_class)->dispose(object);
}

static void main_win_init(MainWin *self)
{
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

    // Create widgets for layout
    self->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->entry_add = gtk_entry_new();
    self->btn_add = gtk_button_new_with_label("Add Item");
    self->btn_remove = gtk_button_new_with_label("Remove Item");
    self->btn_remove_all = gtk_button_new_with_label("Remove All Item");
    self->scrolled_window = gtk_scrolled_window_new();

    // Link signals
    g_signal_connect(self->btn_add, "clicked", G_CALLBACK(btnadd_clicked), self);
    g_signal_connect(self->btn_remove, "clicked", G_CALLBACK(btnremove_clicked), self);
    g_signal_connect(self->btn_remove_all, "clicked", G_CALLBACK(btnremove_all_clicked), self);

    // Add widgets to the layout
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(self->scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_hexpand(self->scrolled_window, TRUE);
    gtk_widget_set_vexpand(self->scrolled_window, TRUE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(self->scrolled_window), self->view);
    gtk_box_append(GTK_BOX(self->main_box), self->scrolled_window);
    gtk_box_append(GTK_BOX(self->main_box), self->entry_add);
    gtk_box_append(GTK_BOX(self->main_box), self->btn_add);
    gtk_box_append(GTK_BOX(self->main_box), self->btn_remove);
    gtk_box_append(GTK_BOX(self->main_box), self->btn_remove_all);
    gtk_window_set_child(GTK_WINDOW(self), self->main_box);
}

static void main_win_class_init(MainWinClass *klass)
{
    G_OBJECT_CLASS(klass)->dispose = main_win_dispose;
}

MainWin *main_win_new(GtkApplication *app)
{
    return MAIN_WIN(g_object_new(main_win_get_type(), "application", app, NULL));
}
