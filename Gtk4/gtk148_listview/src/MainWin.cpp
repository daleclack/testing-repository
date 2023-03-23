#include "MainWin.hh"

struct _MainWin{
    GtkApplicationWindow parent_instance;
    GListModel *model;
    GtkListView *view;
};

G_DEFINE_TYPE(MainWin, main_win, GTK_TYPE_APPLICATION_WINDOW)

static GListModel *create_list_model()
{
    GListStore *store;

    // Create the list store
    store = g_list_store_new(G_TYPE_STRING);

    // Fill the store
    g_list_store_append(store, g_string_new("Item 1"));
    g_list_store_append(store, g_string_new("Item 2"));
    g_list_store_append(store, g_string_new("Item 3"));

    return G_LIST_MODEL(store);
}

static void main_win_init(MainWin *self){

}

static void main_win_class_init(MainWinClass *klass){
}

MainWin *main_win_new(GtkApplication *app){
    return MAIN_WIN(g_object_new(main_win_get_type(), "application", app, NULL));
}
