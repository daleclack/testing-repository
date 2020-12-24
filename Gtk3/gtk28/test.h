#include <gtk/gtk.h>

void print(GtkWidget *widget,gpointer data);

void quit(GtkWidget *widget,gpointer data);

void config_activate(GtkWidget *widget,gpointer data);

void InputBox(const char *filename);

void MsgBox(const gchar *title,const gchar *msg);

void config_activate(GtkWidget *widget,gpointer data);

void about_activate(GtkWidget *widget,gpointer data);
