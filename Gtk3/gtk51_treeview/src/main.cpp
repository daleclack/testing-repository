#include <gtk/gtk.h>

enum{
    COLUMN = 0,
    NUM_COLS
};

void on_changed(GtkTreeSelection *select,GtkStatusbar *status){
    GtkTreeIter iter;
    GtkTreeModel *model;
    char *str;
    if(gtk_tree_selection_get_selected(select,&model,&iter)){
        gtk_tree_model_get(model,&iter,COLUMN,&str,-1);
        gtk_statusbar_push(status,gtk_statusbar_get_context_id(status,str),str);   
        g_free(str);
    }
 
}

static GtkTreeModel *create_model(void){
    //Create a treestore and fill the store
    GtkTreeStore *treestore;
    GtkTreeIter toplevel,child;
    treestore=gtk_tree_store_new(NUM_COLS,G_TYPE_STRING);
    gtk_tree_store_append(treestore,&toplevel,NULL);
    gtk_tree_store_set(treestore,&toplevel,COLUMN,"List 1",-1);
    gtk_tree_store_append(treestore,&child,&toplevel);
    gtk_tree_store_set(treestore,&child,COLUMN,"Item 1",-1);
    gtk_tree_store_append(treestore,&child,&toplevel);
    gtk_tree_store_set(treestore,&child,COLUMN,"Item 2",-1);
    gtk_tree_store_append(treestore,&child,&toplevel);
    gtk_tree_store_set(treestore,&child,COLUMN,"Item 3",-1);
    gtk_tree_store_append(treestore,&child,&toplevel);
    gtk_tree_store_set(treestore,&child,COLUMN,"Item 4",-1);
    gtk_tree_store_append(treestore,&toplevel,NULL);
    gtk_tree_store_set(treestore,&toplevel,COLUMN,"List 2",-1);
    gtk_tree_store_append(treestore,&child,&toplevel);
    gtk_tree_store_set(treestore,&child,COLUMN,"Item 5",-1);
    gtk_tree_store_append(treestore,&child,&toplevel);
    gtk_tree_store_set(treestore,&child,COLUMN,"Item 6",-1);
    gtk_tree_store_append(treestore,&child,&toplevel);
    gtk_tree_store_set(treestore,&child,COLUMN,"Item 7",-1);
    return GTK_TREE_MODEL(treestore);
}

static GtkWidget *create_view_and_model(void){
    GtkTreeViewColumn *col;
    GtkCellRenderer *render;
    GtkTreeModel *model;
    GtkWidget *view;
    //Create a treeview widget
    view=gtk_tree_view_new();
    //Append column to show selection
    col=gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(col,"Tree List");
    gtk_tree_view_append_column(GTK_TREE_VIEW(view),col);
    //renderer to shoe the text
    render=gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(col,render,TRUE);
    gtk_tree_view_column_add_attribute(col,render,"text",COLUMN);
    //model as a store
    model=create_model();
    gtk_tree_view_set_model(GTK_TREE_VIEW(view),model);
    g_object_unref(model);
    return view;
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*treeview,*vbox,*statusbar,*sw;
    GtkTreeSelection *select;
    //Main window
    window=gtk_application_window_new(app);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(window),350,300);
    //Veritcal box
    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    //GtkTreeView
    treeview=create_view_and_model();
    //Scrolled window
    sw=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(sw),treeview);
    gtk_box_pack_start(GTK_BOX(vbox),sw,TRUE,TRUE,0);
    //Statusbar
    statusbar=gtk_statusbar_new();
    gtk_box_pack_end(GTK_BOX(vbox),statusbar,FALSE,TRUE,1); 
    //Selection
    select=gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    g_signal_connect(select,"changed",G_CALLBACK(on_changed),statusbar);

    gtk_container_add(GTK_CONTAINER(window),vbox);
    gtk_widget_show_all(window);
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run(G_APPLICATION(app),argc,argv);
}
