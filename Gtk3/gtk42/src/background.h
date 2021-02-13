#include <gtk/gtk.h>
#ifndef __BACK_H_
#define __BACK_H_


void default_background(GtkBuilder *builder);

void fileopen(GtkWidget *widget,GtkBuilder *builder);

void dialog_response(GtkWidget *widget,int response,GtkBuilder *builder);


#endif

