#pragma once

#include "mywindow.h"

#define MY_DIALOG_TYPE (my_dialog_get_type())
G_DECLARE_FINAL_TYPE(MyDialog,my_dialog,MY,DIALOG,GtkFileChooserDialog)

MyDialog * my_dialog_new(MyWindow *window);
