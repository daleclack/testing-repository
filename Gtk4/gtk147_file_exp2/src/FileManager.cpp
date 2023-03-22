#include "FileManager.h"

struct _FileManager{
    GtkWindow parent_instance;
};

G_DEFINE_TYPE(FileManager, file_manager, GTK_TYPE_WINDOW)

static void file_manager_init(FileManager *self){
    // Create file for directory
    GFile *file = g_file_new_for_path(g_get_home_dir());

    // Create List item factory
    GtkListItemFactory *factory = gtk_signal_list_item_factory_new();

    // Create list model
    GtkDirectoryList *list_model = gtk_directory_list_new("local_only", file);
    GtkWidget *view = gtk_list_view_new(GTK_SELECTION_MODEL(
                      gtk_single_selection_new(G_LIST_MODEL(list_model))), factory);
    
    // Add widget to the window
    gtk_window_set_child(GTK_WINDOW(self), view);
}

static void file_manager_class_init(FileManagerClass *klass){

}

FileManager *file_manager_new(){
    return FILE_MANAGER(g_object_new(file_manager_get_type(), NULL));
}
