#include <gtk/gtk.h>

void gtkwin(GtkApplication *app,gpointer user_data);

void gtk_win_add_menu(GtkWidget *widget,gpointer data);

void gtk_layout_add_widgets(GtkWidget *widget,gpointer data);

void button_click(GtkWidget *widget,gpointer data);

void MsgBox(GtkWidget *widget,gpointer data,const gchar *str);

void InputBox(GtkWidget *widget,gpointer data);

void config1(GtkWidget *widget,gpointer data);

void entry_activate(GtkWidget *widget,gpointer data);

void about(GtkWidget *widget,gpointer data);
//This header defines a gtk window and some widgets
