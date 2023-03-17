#include "FileManager.h"

struct _FileManager{
    GtkWindow parent_instance;
};

G_DEFINE_TYPE(FileManager, file_manager, GTK_TYPE_WINDOW)

static void file_manager_init(FileManager *self){

}

static void file_manager_class_init(FileManagerClass *klass){

}

FileManager *file_manager_new(){
    return FILE_MANAGER(g_object_new(file_manager_get_type(), NULL));
}
