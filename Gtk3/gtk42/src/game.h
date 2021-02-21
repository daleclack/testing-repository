#ifndef __GAME_H_
#define __GAME_H_

#include <gtk/gtk.h>
#include <ctime>
#include <cstdlib>
#include <cstring>

void btn_click(GtkWidget *widget,gpointer data);

void buttons_init(GtkBuilder *builder);

void btngo_click(GtkWidget *widget,gpointer data);

void gamemain(GtkWidget *widget,GtkWindow *parent);

#endif
