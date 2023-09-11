#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(MyMsgBox, my_msgbox, MY, MSGBOX, GtkWindow)

MyMsgBox *my_msgbox_new(GtkWindow *parent);

void my_msgbox_show(MyMsgBox *msg_box, const char *message);
