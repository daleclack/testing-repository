#include <gtk/gtk.h>

enum{
    LIST_ITEM=0,
    N_COLUMNS
};

static GtkWidget *list;

static void add_item(GtkWidget *widget,GtkEntry *entry){
    //Add item list
    GtkListStore *store;
    GtkTreeIter iter;
    const char *str=gtk_entry_get_text(entry);
    store=GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    gtk_list_store_append(store,&iter);
    gtk_list_store_set(store,&iter,LIST_ITEM,str,-1);
}

static void remove_item(GtkWidget *widget,GtkTreeSelection *select){
    //Remove the selected item
    GtkListStore *store;
    GtkTreeModel *model;
    GtkTreeIter iter;
    model=gtk_tree_view_get_model(GTK_TREE_VIEW(list));
    store=GTK_LIST_STORE(model);
    if(gtk_tree_model_get_iter_first(model,&iter)==FALSE)
        return ;
    if(gtk_tree_selection_get_selected(select,&model,&iter))
        gtk_list_store_remove(store,&iter);
}

static void remove_all(GtkWidget *widget,gpointer select){
    //Remove All item
    GtkListStore *store;
    GtkTreeModel *model;
    GtkTreeIter iter;
    model=gtk_tree_view_get_model(GTK_TREE_VIEW(list));
    store=GTK_LIST_STORE(model);
    if(gtk_tree_model_get_iter_first(model,&iter)==FALSE)
        return ;
    gtk_list_store_clear(store);
}

static void init_list(GtkWidget *list){
    //Initalize list
    GtkListStore *store;
    GtkTreeViewColumn *column;
    GtkCellRenderer *render;
    render=gtk_cell_renderer_text_new();
    column=gtk_tree_view_column_new_with_attributes("List 1",render,"text",LIST_ITEM,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list),column);
    store=gtk_list_store_new(N_COLUMNS,G_TYPE_STRING);
    gtk_tree_view_set_model(GTK_TREE_VIEW(list),GTK_TREE_MODEL(store));
    g_object_unref(store);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*vbox,*entry,*btnadd,*remove,*removeAll,*sw;
    GtkTreeSelection *select;
    //Main window
    window=gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window),270,400);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    //Vertical box
    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    //Scrolled window
    sw=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw),GTK_SHADOW_IN);
    //List widget
    list=gtk_tree_view_new();
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list),FALSE);
    //Entry and buttons
    entry=gtk_entry_new();
    btnadd=gtk_button_new_with_label("Add Item");
    remove=gtk_button_new_with_label("Remove Item");
    removeAll=gtk_button_new_with_label("Remove All");
    gtk_box_pack_start(GTK_BOX(vbox),sw,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),entry,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),btnadd,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),remove,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),removeAll,FALSE,FALSE,0);
    //Initalize list and get selection
    init_list(list);
    select=gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
    g_signal_connect(btnadd,"clicked",G_CALLBACK(add_item),entry);
    g_signal_connect(remove,"clicked",G_CALLBACK(remove_item),select);
    g_signal_connect(removeAll,"clicked",G_CALLBACK(remove_all),select);
    gtk_container_add(GTK_CONTAINER(sw),list);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    gtk_widget_show_all(window);
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}