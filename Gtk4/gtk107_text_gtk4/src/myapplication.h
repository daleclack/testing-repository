#pragma once

#include <gtk/gtk.h>

#define MY_APPLICATION_TYPE (my_application_get_type())
G_DECLARE_FINAL_TYPE(MyApplication,my_application,MY,APPLICATION,GtkApplication)

MyApplication * my_application_new();
