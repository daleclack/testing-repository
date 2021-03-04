#include <gtk/gtk.h>

enum{
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

static void list_init(GtkWidget *list){
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

void on_changed(GtkTreeSelection *select,GtkLabel *label){
    GtkTreeIter iter;
    GtkTreeModel *model;
    char *str;
    if(gtk_tree_selection_get_selected(select,&model,&iter)){
        gtk_tree_model_get(model,&iter,LIST_ITEM,&str,-1);
        gtk_label_set_label(label,str);
        g_free(str);
    }
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*vbox,*list,*btnExit,*label;
    GtkTreeSelection *select;
    //Creata the main window
    window=gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"gtk(48)");
    gtk_window_set_default_size(GTK_WINDOW(window),270,300);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    //Treeview as List
    list=gtk_tree_view_new();
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list),FALSE);
    //label
    label=gtk_label_new("No Item Selected");
    gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_CENTER);
    //"Exit" button
    btnExit=gtk_button_new_with_label("Exit");
    g_signal_connect_swapped(btnExit,"clicked",G_CALLBACK(gtk_widget_destroy),window);
    //Initalize list
    list_init(list);
    add_to_list(list,"Item1");
    add_to_list(list,"Item2");
    add_to_list(list,"Item3");
    add_to_list(list,"Item4");
    add_to_list(list,"Item5");
    //Get the selection
    select=gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
    g_signal_connect(select,"changed",G_CALLBACK(on_changed),label);
    //The Vertical GtkBox
    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_box_pack_start(GTK_BOX(vbox),list,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),btnExit,TRUE,TRUE,0);

    gtk_container_add(GTK_CONTAINER(window),vbox);
    gtk_widget_show_all(window);
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
