#ifndef __MYDIALOG_H_
#define __MYDIALOG_H_

#include <gtk/gtk.h>

#define MY_DIALOG_TYPE (my_dialog_get_type())

G_DECLARE_FINAL_TYPE(MyDialog,my_dialog,MY,DIALOG,GtkDialog)

MyDialog * my_dialog_new(void);

void set_filename(MyDialog *dialog,const char *filename);

#endif
