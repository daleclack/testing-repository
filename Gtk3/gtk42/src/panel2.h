#ifndef __PANEL2_H_
#define __PANEL2_H_

#include <gtk/gtk.h>

void add_leftpanel(GtkBuilder *builder,GtkFixed *fixed);

void btnvlc_clicked(GtkWidget *widget,gpointer data);

void btngedit_clicked(GtkWidget *widget,gpointer data);

#endif
