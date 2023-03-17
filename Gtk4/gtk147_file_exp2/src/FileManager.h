#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(FileManager, file_manager, FILE, MANAGER, GtkWindow)

FileManager *file_manager_new();
