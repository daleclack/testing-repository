#pragma once

#include "myapplication.h"

#define MY_WINDOW_TYPE (my_window_get_type())
G_DECLARE_FINAL_TYPE(MyWindow,my_window,MY,WINDOW,GtkApplicationWindow)

MyWindow * my_window_new(MyApplication * app);

void my_window_open(MyWindow *window,GFile *file);
