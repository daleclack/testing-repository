#include <gtk/gtk.h>

enum {
    LIST_ITEM = 0,
    N_COLUMNS
};

static void add_to_list(GtkWidget *list,const gchar *str){
    GtkListStore *store;
    GtkTreeIter iter;
    store=GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    gtk_list_store_append(store,&iter);
    gtk_list_store_set(store,&iter,LIST_ITEM,str,-1);
}

static void init_list(GtkWidget *list){
    GtkCellRenderer *render;
    GtkTreeViewColumn *column;
    GtkListStore *store;
    render=gtk_cell_renderer_text_new();
    column=gtk_tree_view_column_new_with_attributes("List Items",render,"text",LIST_ITEM,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list),column);
    store=gtk_list_store_new(N_COLUMNS,G_TYPE_STRING);
    gtk_tree_view_set_model(GTK_TREE_VIEW(list),GTK_TREE_MODEL(store));
    g_object_unref(store);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*list,*vbox,*label;
    GtkTreeSelection *selection;
    //Main window
    window=gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window),270,250);
    gtk_window_set_title(GTK_WINDOW(window),"gtk(47)");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    //TreeView Widget
    list=gtk_tree_view_new();
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list),FALSE);
    //Label to show
    label=gtk_label_new("");
    gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_CENTER);

    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_box_pack_start(GTK_BOX(vbox),list,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);

    init_list(list);
    add_to_list(list,"List1");
    add_to_list(list,"List2");
    add_to_list(list,"List3");
    add_to_list(list,"List4");
    add_to_list(list,"List5");

    gtk_container_add(GTK_CONTAINER(window),vbox);
    gtk_widget_show_all(window);
}

int main(int argc,char *argv[])
{
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
