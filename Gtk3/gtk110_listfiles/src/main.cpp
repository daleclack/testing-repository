#include <gtk/gtk.h>

#define FOLDER_NAME "/gtk110/gnome-fs-directory.png"
#define FILE_NAME "/gtk110/gnome-fs-regular.png"

enum{
   COL_PATH,
   COL_DISPLAY_NAME,
   COL_PIXBUF,
   COL_IS_DIRECTORY,
   NUM_COLS
};

static GdkPixbuf *file_pixbuf, *folder_pixbuf;
static char *parent;
static GtkToolItem *up_button,*show_hidden;

static void load_pixbufs(void){
    GdkPixbuf *tmp1,*tmp2;
    if(file_pixbuf){    //Already loaded
        return ;
    }

    tmp1=gdk_pixbuf_new_from_resource(FILE_NAME,NULL);
    file_pixbuf=gdk_pixbuf_scale_simple(tmp1,16,16,GDK_INTERP_BILINEAR);
    //Check load state
    g_assert(file_pixbuf);
    g_object_unref(tmp1);

    tmp2=gdk_pixbuf_new_from_resource(FOLDER_NAME,NULL);
    folder_pixbuf=gdk_pixbuf_scale_simple(tmp2,16,16,GDK_INTERP_BILINEAR);
    g_assert(folder_pixbuf);
    g_object_unref(tmp2);
}

static void fill_store(GtkListStore *store){
    GDir * dir;
    const gchar *name;
    GtkTreeIter iter;

    //Clear the store
    gtk_list_store_clear(store);

    //Go through the directory and get information
    dir=g_dir_open(parent,0,NULL);
    if(!dir){
        return;
    }

    /* Ignore the files start with '.' when the button is not toggled */
    name=g_dir_read_name(dir);
    while(name!=NULL){
        gchar *path, *display_name;
        gboolean is_dir;

        if(name[0]=='.' && !gtk_toggle_tool_button_get_active(GTK_TOGGLE_TOOL_BUTTON(show_hidden))){
            name=g_dir_read_name(dir);
            continue;
        }

        path = g_build_filename(parent, name, NULL);

        is_dir = g_file_test(path, G_FILE_TEST_IS_DIR);

        display_name = g_filename_to_utf8(name, -1, NULL, NULL, NULL);

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           COL_PATH, path,
                           COL_DISPLAY_NAME, display_name,
                           COL_IS_DIRECTORY, is_dir,
                           COL_PIXBUF, is_dir ? folder_pixbuf : file_pixbuf,
                           -1);
        g_free (path);
        g_free (display_name);
        name=g_dir_read_name(dir);
    }
    g_dir_close(dir);
}

static int sort_func(GtkTreeModel *model,
                     GtkTreeIter  *a,
                     GtkTreeIter  *b,
                     gpointer      user_data)
{
    gboolean is_dir_a,is_dir_b;
    gchar *name_a,*name_b;
    int ret;

    //Sort Folders before files,
    //and sort files and folders starts with a '.' in front of other files and folders
    gtk_tree_model_get(model,a,COL_IS_DIRECTORY,&is_dir_a,COL_DISPLAY_NAME,&name_a,-1);
    gtk_tree_model_get(model,b,COL_IS_DIRECTORY,&is_dir_b,COL_DISPLAY_NAME,&name_b,-1);

    if(!is_dir_a && is_dir_b){
        ret = 1;
    }else if(is_dir_a && !is_dir_b){
        ret = -1;
    }else if(name_a[0]!='.' && name_b[0]=='.'){
        ret = 1;
    }else if(name_a[0]=='.' && name_b[0]!='.'){
        ret = -1;
    }else{
        ret = g_utf8_collate(name_a,name_b);
    }
    g_free(name_a);
    g_free(name_b);

    return ret;
}

static GtkListStore* create_store(void){
    GtkListStore *store;

    store=gtk_list_store_new(NUM_COLS,
                             G_TYPE_STRING,
                             G_TYPE_STRING,
                             GDK_TYPE_PIXBUF,
                             G_TYPE_BOOLEAN);
    
    gtk_tree_sortable_set_default_sort_func(GTK_TREE_SORTABLE(store),
                                            sort_func,NULL,NULL);

    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(store),
                                         GTK_TREE_SORTABLE_DEFAULT_SORT_COLUMN_ID,
                                         GTK_SORT_ASCENDING);

    return store;
}

static void item_activated(GtkTreeView *view,GtkTreePath *tree_path,GtkTreeViewColumn *column,gpointer data){
    GtkListStore *store;
    gchar *path;
    GtkTreeIter iter;
    gboolean is_dir;

    store=GTK_LIST_STORE(data);

    gtk_tree_model_get_iter(GTK_TREE_MODEL(store),&iter,tree_path);
    gtk_tree_model_get(GTK_TREE_MODEL(store),&iter,COL_PATH,&path,COL_IS_DIRECTORY,&is_dir,-1);

    if(!is_dir)
    {
      g_free(path);
      return;
    }

    /* Replace parent with path and re-fill the model*/
    g_free(parent);
    parent = path;

    fill_store(store);

    /* Sensitize the up button */
    gtk_widget_set_sensitive(GTK_WIDGET(up_button),TRUE);
}

static void show_clicked(GtkToolItem *item,gpointer data){
    GtkListStore * store;
    store=GTK_LIST_STORE(data);
    fill_store(store);
}

static void up_clicked(GtkToolItem *item,gpointer data){
    GtkListStore * store;
    gchar *dir_name;

    store = GTK_LIST_STORE(data);

    dir_name = g_path_get_dirname(parent);
    g_free(parent);

    parent = dir_name;
    fill_store(store);

    //Set Up button to sensitive
    gtk_widget_set_sensitive(GTK_WIDGET(up_button),TRUE);
}

static void home_clicked(GtkToolItem *item,gpointer data){
    GtkListStore * store;

    store = GTK_LIST_STORE(data);

    g_free(parent);
    parent = g_strdup(g_get_home_dir());

    fill_store(store);

    //Set Up button to sensitive
    gtk_widget_set_sensitive(GTK_WIDGET(up_button),TRUE);    
}

static void close_window(GtkWidget *widget,gpointer data){
    gtk_widget_destroy(widget);
    widget=NULL;

    g_object_unref(file_pixbuf);
    file_pixbuf=NULL;

    g_object_unref(folder_pixbuf);
    folder_pixbuf=NULL;

}

static void gtkmain(GtkApplication* app,gpointer user_data){
    GtkWidget *window,*sw,*tree_view,*vbox,*tool_bar;
    GtkToolItem *home_button;
    GtkListStore *store;
    GtkCellRenderer *icon_render,*text_render;
    GtkTreeViewColumn *column;

    //Initalize window
    window=gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window),650,400);
    gtk_window_set_title(GTK_WINDOW(window),"File Manager");
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    g_signal_connect(window,"destroy",G_CALLBACK(close_window),NULL);

    load_pixbufs();

    //Create child widgets
    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);

    tool_bar=gtk_toolbar_new();
    gtk_box_pack_start(GTK_BOX(vbox),tool_bar,FALSE,FALSE,0);

    up_button=gtk_tool_button_new(NULL,NULL);
    gtk_tool_button_set_label(GTK_TOOL_BUTTON(up_button),"_Up");
    gtk_tool_button_set_use_underline(GTK_TOOL_BUTTON(up_button),TRUE);
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(up_button),"go-up");
    gtk_tool_item_set_is_important(up_button,TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(up_button),FALSE);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar),up_button,-1);

    home_button = gtk_tool_button_new(NULL,NULL);
    gtk_tool_button_set_label(GTK_TOOL_BUTTON(home_button),"_Home");
    gtk_tool_button_set_use_underline(GTK_TOOL_BUTTON(home_button),TRUE);
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(home_button),"go-home");
    gtk_tool_item_set_is_important(home_button,TRUE);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar),home_button,-1);

    show_hidden = gtk_toggle_tool_button_new();
    gtk_tool_button_set_label(GTK_TOOL_BUTTON(show_hidden),"Show Hidden Files");
    gtk_tool_button_set_use_underline(GTK_TOOL_BUTTON(show_hidden),TRUE);
    gtk_tool_item_set_is_important(show_hidden,TRUE);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar),show_hidden,-1);


    sw = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw),GTK_SHADOW_ETCHED_IN);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (sw),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox),sw,TRUE,TRUE, 0);

    //Create Store and fill it
    parent=g_strdup("/");
    store=create_store();
    fill_store(store);

    tree_view=gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    //gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(tree_view),GTK_SELECTION_MULTIPLE);

    g_object_unref(store);

    /* Connect to the "clicked" signal of the "Up" tool button */
    g_signal_connect(up_button, "clicked",
                     G_CALLBACK (up_clicked), store);

    /* Connect to the "clicked" signal of the "Home" tool button */
    g_signal_connect(home_button, "clicked",
                     G_CALLBACK (home_clicked), store);

    /* Connect to the "clicked" signal of the "Show hidden files" tool button */
    g_signal_connect(show_hidden, "clicked",
                     G_CALLBACK (show_clicked), store);

    /* We now set which model columns that correspond to the text
    * and pixbuf of each item
    */
    icon_render=gtk_cell_renderer_pixbuf_new();
    text_render=gtk_cell_renderer_text_new();
    column=gtk_tree_view_column_new_with_attributes("",icon_render,"pixbuf",COL_PIXBUF,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),column);
    column=gtk_tree_view_column_new_with_attributes("Name",text_render,"text",COL_DISPLAY_NAME,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),column);
    

    /* Connect to the "item-activated" signal */
    g_signal_connect(tree_view, "row-activated",
                     G_CALLBACK (item_activated), store);

    gtk_container_add(GTK_CONTAINER(sw),tree_view);

    gtk_widget_show_all(window);
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    int status=g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    return status;
}
