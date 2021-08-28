#ifndef __MYAPP_H_
#define __MYAPP_H_

#include <gtk/gtk.h>

#define MY_APP_TYPE (my_app_get_type())
G_DECLARE_FINAL_TYPE(MyApp,my_app,MY,APP,GtkApplication)

MyApp * my_app_new(void);

#endif
