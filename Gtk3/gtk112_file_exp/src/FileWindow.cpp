#include "FileWindow.h"

#define FOLDER_NAME "/gtk112/gnome-fs-directory.png"
#define FILE_NAME "/gtk112/gnome-fs-regular.png"

//IconView and TreeView Model
enum{
   COL_PATH,
   COL_DISPLAY_NAME,
   COL_PIXBUF,
   COL_IS_DIRECTORY,
   NUM_COLS
};

//ComboBox model
enum{
    COMBO_PIXBUF,
    COMBO_COLS
};

struct _FileWindow{
    GtkApplicationWindow parent;
    GdkPixbuf *file_pixbuf, *folder_pixbuf;
    char *parent_dir;
    GtkToolItem *up_button;
    GtkWidget *stack, *show_hidden, *view_combo, *tree_view, *icon_view;
    GtkListStore *store;
    GList *selected_items;
};

G_DEFINE_TYPE(FileWindow,file_window,GTK_TYPE_APPLICATION_WINDOW)

static void file_window_load_pixbufs(int size,FileWindow *win){
    GdkPixbuf *tmp1,*tmp2;
    if(win->file_pixbuf){    //Already loaded
        return ;
    }

    tmp1=gdk_pixbuf_new_from_resource(FILE_NAME,NULL);
    win->file_pixbuf=gdk_pixbuf_scale_simple(tmp1,size,size,GDK_INTERP_BILINEAR);
    //Check load state
    g_assert(win->file_pixbuf);
    g_object_unref(tmp1);

    tmp2=gdk_pixbuf_new_from_resource(FOLDER_NAME,NULL);
    win->folder_pixbuf=gdk_pixbuf_scale_simple(tmp2,size,size,GDK_INTERP_BILINEAR);
    g_assert(win->folder_pixbuf);
    g_object_unref(tmp2);
}

static void file_window_fill_store(FileWindow *win){
    GDir * dir;
    const gchar *name;
    GtkTreeIter iter;

    //Clear the store
    gtk_list_store_clear(win->store);

    //Go through the directory and get information
    dir=g_dir_open(win->parent_dir,0,NULL);
    if(!dir){
        return;
    }

    /* Ignore the files start with '.' when the button is not toggled */
    name=g_dir_read_name(dir);
    while(name!=NULL){
        gchar *path, *display_name;
        gboolean is_dir;

        if(name[0]=='.' && !gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(win->show_hidden))){
            name=g_dir_read_name(dir);
            continue;
        }

        path = g_build_filename(win->parent_dir, name, NULL);

        is_dir = g_file_test(path, G_FILE_TEST_IS_DIR);

        display_name = g_filename_to_utf8(name, -1, NULL, NULL, NULL);

        gtk_list_store_append(win->store, &iter);
        gtk_list_store_set(win->store, &iter,
                           COL_PATH, path,
                           COL_DISPLAY_NAME, display_name,
                           COL_IS_DIRECTORY, is_dir,
                           COL_PIXBUF, is_dir ? win->folder_pixbuf : win->file_pixbuf,
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

static void row_activated(GtkTreeView *view,GtkTreePath *tree_path,GtkTreeViewColumn *column,FileWindow *win){
    gchar *path;
    GtkTreeIter iter;
    gboolean is_dir;

    gtk_tree_model_get_iter(GTK_TREE_MODEL(win->store),&iter,tree_path);
    gtk_tree_model_get(GTK_TREE_MODEL(win->store),&iter,COL_PATH,&path,COL_IS_DIRECTORY,&is_dir,-1);

    if(!is_dir)
    {
      g_free(path);
      return;
    }

    /* Replace parent with path and re-fill the model*/
    g_free(win->parent_dir);
    win->parent_dir = path;

    file_window_fill_store(win);

    /* Sensitize the up button */
    gtk_widget_set_sensitive(GTK_WIDGET(win->up_button),TRUE);
}

static void item_activated(GtkIconView *view,GtkTreePath *tree_path,FileWindow *win){
    gchar *path;
    GtkTreeIter iter;
    gboolean is_dir;

    gtk_tree_model_get_iter(GTK_TREE_MODEL(win->store),&iter,tree_path);
    gtk_tree_model_get(GTK_TREE_MODEL(win->store),&iter,COL_PATH,&path,COL_IS_DIRECTORY,&is_dir,-1);

    if(!is_dir)
    {
      g_free(path);
      return;
    }

    /* Replace parent with path and re-fill the model*/
    g_free(win->parent_dir);
    win->parent_dir = path;

    file_window_fill_store(win);

    /* Sensitize the up button */
    gtk_widget_set_sensitive(GTK_WIDGET(win->up_button),TRUE);
}

static void up_clicked(GtkToolItem *item,FileWindow *win){
    gchar *dir_name;

    dir_name = g_path_get_dirname(win->parent_dir);
    g_free(win->parent_dir);

    win->parent_dir = dir_name;
    file_window_fill_store(win);

    //Set Up button to sensitive
    gtk_widget_set_sensitive(GTK_WIDGET(win->up_button),TRUE);
}

static void home_clicked(GtkToolItem *item,FileWindow *win){
    g_free(win->parent_dir);
    win->parent_dir = g_strdup(g_get_home_dir());

    file_window_fill_store(win);

    //Set Up button to sensitive
    gtk_widget_set_sensitive(GTK_WIDGET(win->up_button),TRUE);    
}

static void view_changed(GtkComboBox * combo,FileWindow *win){
    int view_mode=gtk_combo_box_get_active(combo);
    if(view_mode){
        gtk_stack_set_visible_child_name(GTK_STACK(win->stack),"List_view");
    }else{
        gtk_stack_set_visible_child_name(GTK_STACK(win->stack),"Icon_view");
    }
}

static void make_directory(GtkWidget *widget,int response,GtkEntry *entry){
    //Make a new directory
    if(response == GTK_RESPONSE_OK){
        FileWindow *win=FILE_WINDOW(gtk_window_get_transient_for(GTK_WINDOW(widget)));
        const char *folder=gtk_entry_get_text(entry);
        char *path, *parent_path;
        parent_path=win->parent_dir;
        if(strlen(parent_path) == 1 && parent_path[0] == '/'){
            path=g_strdup_printf("%s%s",parent_path,folder);
        }else{
            path=g_strdup_printf("%s/%s",parent_path,folder);
        }
        if(g_mkdir_with_parents(path,0755) == -1){
            g_print("Error Occured!");
        }else{
            file_window_fill_store(win);
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

static GtkWidget * create_list_view(FileWindow *win){
    GtkWidget * tree_view;
    GtkCellRenderer *icon_render,*text_render;
    GtkTreeViewColumn *column;

    tree_view=gtk_tree_view_new_with_model(GTK_TREE_MODEL(win->store));
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
                     G_CALLBACK (row_activated), win);

    return tree_view;
}

static GtkWidget * create_icon_view(FileWindow *win){
    GtkWidget *icon_view;

    icon_view=gtk_icon_view_new_with_model(GTK_TREE_MODEL(win->store));
    gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(icon_view),GTK_SELECTION_MULTIPLE);

    /* We now set which model columns that correspond to the text
    * and pixbuf of each item
    */
    gtk_icon_view_set_text_column(GTK_ICON_VIEW(icon_view),COL_DISPLAY_NAME);
    gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(icon_view),COL_PIXBUF);

    /* Connect to the "item-activated" signal */
    g_signal_connect(icon_view, "item-activated",
                     G_CALLBACK (item_activated), win);

    return icon_view;
}

static GtkWidget * create_view_combo(void){
    GtkWidget * combo_box;

    combo_box=gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box),"Icon");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box),"List");

    return combo_box;
}

GtkWidget * create_delete_dialog(FileWindow *win,const char *msg){
    //Message Dialog
    GtkWidget *dialog, *hbox, *content_area, *label, *error_image, *label1, *vbox;
    char * msg_str=g_strdup_printf("Delete Failed:%s",msg);

    if(!msg){
        return NULL;
    }

    dialog = gtk_dialog_new_with_buttons("File",GTK_WINDOW(win),GTK_DIALOG_DESTROY_WITH_PARENT,
             "OK",GTK_RESPONSE_OK,NULL);
    gtk_window_set_default_size(GTK_WINDOW(dialog),300,150);
    gtk_window_set_icon_name(GTK_WINDOW(dialog),"org.gtk.daleclack");

    //Child Widgets
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    label1 = gtk_label_new("    ");
    gtk_box_pack_start(GTK_BOX(vbox),label1,FALSE,FALSE,0);

    error_image = gtk_image_new_from_resource("/gtk112/dialog-error.png");
    gtk_box_pack_start(GTK_BOX(hbox),error_image,FALSE,FALSE,0);

    label = gtk_label_new(msg_str);
    gtk_box_pack_end(GTK_BOX(hbox),label,FALSE,FALSE,0);

    gtk_widget_set_valign(hbox,GTK_ALIGN_CENTER);
    gtk_widget_set_halign(hbox,GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,0);
    gtk_container_add(GTK_CONTAINER(content_area),vbox);
    g_signal_connect_swapped(dialog,"response",G_CALLBACK(gtk_widget_destroy),dialog);

    g_free(msg_str);
    return dialog;
}

static void btndel_clicked(GtkToolItem *item,FileWindow *win){
    GtkTreeIter iter;
    char * select_name = NULL;
    int view_mode=gtk_combo_box_get_active(GTK_COMBO_BOX(win->view_combo));
    GtkWidget *dialog=NULL;
    switch(view_mode){
        case 0:    //Iconfied Mode
            GList *list,*header;
            list = gtk_icon_view_get_selected_items(GTK_ICON_VIEW(win->icon_view));
            header=list;
            while(list!=NULL){
                GtkTreePath *path = (GtkTreePath*)(list->data);
                if(gtk_tree_model_get_iter(GTK_TREE_MODEL(win->store),&iter,path)){
                    gtk_tree_model_get(GTK_TREE_MODEL(win->store),&iter,COL_DISPLAY_NAME,&select_name,-1);
                    dialog = create_delete_dialog(win,select_name);
                }
                list=list->next;
            }
            g_list_free_full(header, (GDestroyNotify) gtk_tree_path_free);
            break;
        case 1:    //Listed Mode
            GtkTreeSelection *selection;
            selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(win->tree_view));
            GtkTreeModel * model = gtk_tree_view_get_model(GTK_TREE_VIEW(win->tree_view));
            if(gtk_tree_selection_get_selected(selection,&model,&iter)){
                gtk_tree_model_get(model,&iter,COL_DISPLAY_NAME,&select_name,-1);
            }
            //g_object_unref(model);
            dialog = create_delete_dialog(win,select_name);
            g_object_unref(selection);
            break;
    }
    if(dialog){
        gtk_widget_show_all(dialog);
    }
    g_free(select_name);
}

static void file_window_destroy(GtkWidget *widget){
    gtk_widget_destroy(widget);
    widget=NULL;

    g_object_unref(FILE_WINDOW(widget)->file_pixbuf);
    FILE_WINDOW(widget)->file_pixbuf=NULL;

    g_object_unref(FILE_WINDOW(widget)->folder_pixbuf);
    FILE_WINDOW(widget)->folder_pixbuf=NULL;
}

static void file_window_init(FileWindow *window){
    GtkWidget *sw,*vbox,*tool_bar,*btnbox;
    GtkToolItem *home_button,*new_button,*delete_button;

    //Initalize window
    gtk_window_set_default_size(GTK_WINDOW(window),650,400);
    gtk_window_set_title(GTK_WINDOW(window),"File Manager");
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");

    file_window_load_pixbufs(48,window);

    //Create child widgets
    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    btnbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_container_add(GTK_CONTAINER(vbox),btnbox);
    gtk_container_add(GTK_CONTAINER(window),vbox);

    tool_bar=gtk_toolbar_new();
    gtk_box_pack_start(GTK_BOX(btnbox),tool_bar,FALSE,TRUE,0);

    //"Up" Button
    window->up_button=gtk_tool_button_new(NULL,NULL);
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(window->up_button),"go-up");
    gtk_tool_item_set_is_important(window->up_button,TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(window->up_button),FALSE);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar),window->up_button,-1);

    //"Home" Button
    home_button = gtk_tool_button_new(NULL,NULL);
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(home_button),"go-home");
    gtk_tool_item_set_is_important(home_button,TRUE);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar),home_button,-1);

    //"New Folder" Button
    new_button = gtk_tool_button_new(NULL,NULL);
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(new_button),"folder-new");
    gtk_tool_item_set_is_important(new_button,TRUE);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar),new_button,-1);

    //"Delete" Button
    delete_button = gtk_tool_button_new(NULL,NULL);
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(delete_button),"edit-delete");
    gtk_tool_item_set_is_important(delete_button,TRUE);
    gtk_toolbar_insert(GTK_TOOLBAR(tool_bar),delete_button,-1);

    //"View Mode" Combo
    window->view_combo=create_view_combo();
    gtk_combo_box_set_active(GTK_COMBO_BOX(window->view_combo),0);
    gtk_widget_set_valign(window->view_combo,GTK_ALIGN_END);
    gtk_box_pack_end(GTK_BOX(btnbox),window->view_combo,FALSE,FALSE,0);

    //CheckButton for show hidden dir and files
    window->show_hidden=gtk_check_button_new_with_label("Show Hidden Files");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(window->show_hidden),FALSE);
    gtk_widget_set_valign(window->show_hidden,GTK_ALIGN_END);
    gtk_box_pack_end(GTK_BOX(btnbox),window->show_hidden,FALSE,FALSE,0);

    //Folder Container
    sw = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw),GTK_SHADOW_ETCHED_IN);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (sw),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox),sw,TRUE,TRUE,0);

    window->stack=gtk_stack_new();
    
    //Create Store and fill it
    window->parent_dir=g_strdup("/");
    window->store=create_store();
    file_window_fill_store(window);

    window->tree_view=create_list_view(window);
    window->icon_view=create_icon_view(window);

    gtk_stack_add_named(GTK_STACK(window->stack),window->icon_view,"Icon_view");
    gtk_stack_add_named(GTK_STACK(window->stack),window->tree_view,"List_view");

    g_object_unref(window->store);

    /* Connect to the "clicked" signal of the "Up" tool button */
    g_signal_connect(window->up_button, "clicked",
                     G_CALLBACK (up_clicked), window);

    /* Connect to the "clicked" signal of the "Home" tool button */
    g_signal_connect(home_button, "clicked",
                     G_CALLBACK (home_clicked), window);

    /* Connect to the "clicked" signal of the "Show hidden files" tool button */
    g_signal_connect_swapped(window->show_hidden, "clicked",
                             G_CALLBACK (file_window_fill_store), window);

    /* Connect to the "changed" signal of the "View Mode" combo box */
    g_signal_connect(window->view_combo, "changed",
                     G_CALLBACK (view_changed), window);

    /* Connect to the "clicked" signal of the "New Directory" tool button */
    g_signal_connect(new_button, "clicked",
                     G_CALLBACK (btnnew_clicked), window);

    /* Connect to the "clicked" signal of the "Delete" tool button */
    g_signal_connect(delete_button, "clicked",
                     G_CALLBACK (btndel_clicked), window);

    gtk_container_add(GTK_CONTAINER(sw),window->stack);
}

static void file_window_class_init(FileWindowClass *win_class){
    GTK_WIDGET_CLASS(file_window_parent_class)->destroy=file_window_destroy;
}

FileWindow * file_window_new(GtkApplication *app){
    return (FileWindow*)g_object_new(file_window_get_type(),"application",app,NULL);
}
