#ifndef __PANEL2_H_
#define __PANEL2_H_

#include <gtk/gtk.h>

void add_leftpanel(GtkBuilder *builder,GtkFixed *fixed);

void btnvlc_clicked(GtkWidget *widget,gpointer data);

void btngedit_clicked(GtkWidget *widget,gpointer data);

void btnaud_clicked(GtkWidget *widget,gpointer data);

void btnnote_clicked(GtkWidget *widget,gpointer data);

void btnvlc_win32(GtkWidget *widget,gpointer data);

#endif
