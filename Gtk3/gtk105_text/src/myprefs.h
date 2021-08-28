#ifndef __MYPREFS_H_
#define __MYPREFS_H_

#include <gtk/gtk.h>
#include "mywindow.h"

#define MY_PREFS_TYPE (my_prefs_get_type())
G_DECLARE_FINAL_TYPE(MyPrefs,my_prefs,MY,PREFS,GtkDialog)

MyPrefs * my_prefs_new(MyWindow *win);

#endif
