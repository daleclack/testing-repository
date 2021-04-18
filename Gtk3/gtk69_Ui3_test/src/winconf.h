#ifndef __WIN_CONF_H_
#define __WIN_CONF_H_

#include <gtk/gtk.h>

void conf_dialog(GtkWidget *widget,GtkWindow *win);

void conf_response(GtkWidget *widget,int response,GtkBuilder *builder_conf);

void set_default(GtkWidget *widget,GtkBuilder *builder_conf);

void get_winsize(GtkWidget *widget,GtkBuilder *buider_conf);

void get_config(int *width,int *height);


#endif
