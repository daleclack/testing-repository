//This header contains some functions to change GtkWidget proprites
//I use these function to make the "activate" function more simple
//2020.12.8 By:Dale Clack

#include <gtk/gtk.h>

void gtkwin_config(GtkWidget *window);

void image_config(GtkImage *image);

void combo_config(GtkWidget *combo);

void button_config(GtkWidget *button);

void layout_add_label(GtkWidget *label);

void button_click(GtkWidget *widget,GtkWidget *combo);

void MsgBox(GtkWidget *widget,const gchar *str);

void InputBox(GtkWidget *widget,char *str);
