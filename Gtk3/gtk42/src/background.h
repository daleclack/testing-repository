#ifndef __BACK_H_
#define __BACK_H_

#include <gtk/gtk.h>

void default_background(GtkBuilder *builder);

void fileopen(GtkWidget *widget,GtkBuilder *builder);

void dialog_response(GtkWidget *widget,int response,GtkBuilder *builder);


#endif

