#include <gtk/gtk.h>

#define FOLDER_NAME "/gtk111/gnome-fs-directory.png"
#define FILE_NAME "/gtk111/gnome-fs-regular.png"

enum{
   COL_PATH,
   COL_DISPLAY_NAME,
   COL_PIXBUF,
   COL_IS_DIRECTORY,
   NUM_COLS
};

static GdkPixbuf *file_pixbuf, *folder_pixbuf;
static char *parent;
static GtkToolItem *up_button;
static GtkWidget *stack, *show_hidden;

static void load_pixbufs(int size){
    GdkPixbuf *tmp1,*tmp2;
    if(file_pixbuf){    //Already loaded
        return ;
    }

    tmp1=gdk_pixbuf_new_from_resource(FILE_NAME,NULL);
    file_pixbuf=gdk_pixbuf_scale_simple(tmp1,size,size,GDK_INTERP_BILINEAR);
    //Check load state
    g_assert(file_pixbuf);
    g_object_unref(tmp1);

    tmp2=gdk_pixbuf_new_from_resource(FOLDER_NAME,NULL);
    folder_pixbuf=gdk_pixbuf_scale_simple(tmp2,size,size,GDK_INTERP_BILINEAR);
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

        if(name[0]=='.' && !gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(show_hidden))){
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

static void row_activated(GtkTreeView *view,GtkTreePath *tree_path,GtkTreeViewColumn *column,gpointer data){
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

static void item_activated(GtkIconView *view,GtkTreePath *tree_path,gpointer data){
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

static void view_changed(GtkComboBox * combo,gpointer data){
    int view_mode=gtk_combo_box_get_active(combo);
    if(view_mode){
        gtk_stack_set_visible_child_name(GTK_STACK(stack),"List_view");
    }else{
        gtk_stack_set_visible_child_name(GTK_STACK(stack),"Icon_view");
    }
}

static void make_directory(GtkWidget *widget,int response,GtkEntry *entry){
    //Make a new directory
    if(response == GTK_RESPONSE_OK){
        const char *folder=gtk_entry_get_text(entry);
        char * path;
        if(strlen(parent) == 1 && parent[0] == '/'){
            path=g_strdup_printf("%s%s",parent,folder);
        }else{
            path=g_strdup_printf("%s/%s",parent,folder);
        }
        if(g_mkdir_with_parents(path,0755) == -1){
            g_print("Error Occured!");
        }
        g_free(path);
    }
    gtk_widget_destroy(widget);
}

static void btnnew_clicked(GtkToolItem *item,GtkWindow *parent){
    //Create Dialog
    GtkWidget *dialog, *content_area, *entry;
    dialog = gtk_dialog_new_with_buttons("Create a folder",parent,
             GTK_DIALOG_USE_HEADER_BAR,"New",GTK_RESPONSE_OK,"Cancel",GTK_RESPONSE_CANCEL,NULL);
    
    gtk_dialog_set_default_response(GTK_DIALOG(dialog),GTK_RESPONSE_OK);

    //Add entry
    content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    entry=gtk_entry_new();
    gtk_entry_set_activates_default(GTK_ENTRY(entry),TRUE);
    gtk_container_add(GTK_CONTAINER(content_area),entry);

    g_signal_connect(dialog,"response",G_CALLBACK(make_directory),entry);

    gtk_widget_show_all(dialog);
}

static void close_window(GtkWidget *widget,gpointer data){
    gtk_widget_destroy(widget);
    widget=NULL;

    g_object_unref(file_pixbuf);
    file_pixbuf=NULL;

    g_object_unref(folder_pixbuf);
    folder_pixbuf=NULL;

}

static GtkWidget * create_list_view(GtkListStore * store){
    GtkWidget * tree_view;
    GtkCellRenderer *icon_render,*text_render;
    GtkTreeViewColumn *column;

    tree_view=gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    //gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(tree_view),GTK_SELECTION_MULTIPLE);

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
                     G_CALLBACK (row_activated), store);

    return tree_view;
}

static GtkWidget * create_icon_view(GtkListStore * store){
    GtkWidget *icon_view;

    icon_view=gtk_icon_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(icon_view),GTK_SELECTION_MULTIPLE);

    /* We now set which model columns that correspond to the text
    * and pixbuf of each item
    */
    gtk_icon_view_set_text_column(GTK_ICON_VIEW(icon_view),COL_DISPLAY_NAME);
    gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(icon_view),COL_PIXBUF);

    /* Connect to the "item-activated" signal */
    g_signal_connect(icon_view, "item-activated",
                     G_CALLBACK (item_activated), store);

    return icon_view;
}

static void gtkmain(GtkApplication* app,gpointer user_data){
    GtkWidget *window,*sw,*tree_view,*icon_view,*vbox,*tool_bar,*view_combo;
    GtkToolItem *home_button,*view_item,*new_button,*hidden_item;
    GtkListStore *store;
    
    //Initalize window
    window=gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window),650,400);
    gtk_window_set_title(GTK_WINDOW(window),"File Manager");
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");
    g_signal_connect(window,"destroy",G_CALLBACK(close_window),NULL);

    load_pixbufs(48);

    //Create child widgets
    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);

    tool_bar=gtk_toolbar_new();
    gtk_box_pack_start(GTK_BOX(vbox),tool_bar,FALSE,FALSE,0);

    up_button=gtk_tool_button_new(NULL,NULL);
    //gtk_tool_button_set_label(GTK_TOOL_BUTTON(up_button),"_Up");
    //gtk_tool_button_set_use_underline(GTK_TOOL_BUTTON(up_button),TRUE);
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(up_button),"go-up");
    gtk_tool_item_set_is_important(up_button,TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(up_button),FALSE);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar),up_button,-1);

    home_button = gtk_tool_button_new(NULL,NULL);
    //gtk_tool_button_set_label(GTK_TOOL_BUTTON(home_button),"_Home");
    //gtk_tool_button_set_use_underline(GTK_TOOL_BUTTON(home_button),TRUE);
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(home_button),"go-home");
    gtk_tool_item_set_is_important(home_button,TRUE);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar),home_button,-1);

    new_button = gtk_tool_button_new(NULL,NULL);
    //gtk_tool_button_set_label(GTK_TOOL_BUTTON(new_button),"_New Dir");
    //gtk_tool_button_set_use_underline(GTK_TOOL_BUTTON(new_button),TRUE);
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(new_button),"folder-new");
    gtk_tool_item_set_is_important(new_button,TRUE);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar),new_button,-1);

    hidden_item=gtk_tool_item_new();
    show_hidden=gtk_check_button_new_with_label("Show Hidden Files");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(show_hidden),FALSE);
    gtk_container_add(GTK_CONTAINER(hidden_item),show_hidden);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar),hidden_item,-1);

    view_item=gtk_tool_item_new();
    view_combo=gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(view_combo),"Iconfied View");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(view_combo),"Listed View");
    gtk_combo_box_set_active(GTK_COMBO_BOX(view_combo),0);
    gtk_container_add(GTK_CONTAINER(view_item),view_combo);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar),view_item,-1);

    sw = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw),GTK_SHADOW_ETCHED_IN);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (sw),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox),sw,TRUE,TRUE, 0);

    stack=gtk_stack_new();

    //Create Store and fill it
    parent=g_strdup("/");
    store=create_store();
    fill_store(store);

    tree_view=create_list_view(store);
    icon_view=create_icon_view(store);

    gtk_stack_add_named(GTK_STACK(stack),icon_view,"Icon_view");
    gtk_stack_add_named(GTK_STACK(stack),tree_view,"List_view");

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

    /* Connect to the "changed" signal of the "View Mode" combo box */
    g_signal_connect(view_combo, "changed",
                     G_CALLBACK (view_changed), NULL);

    /* Connect to the "clicked" signal of the "New Directory" tool button */
    g_signal_connect(new_button, "clicked",
                     G_CALLBACK (btnnew_clicked), window);

    gtk_container_add(GTK_CONTAINER(sw),stack);

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
