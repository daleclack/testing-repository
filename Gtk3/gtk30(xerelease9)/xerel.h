#include <gtk/gtk.h>

//Show config
void print(GtkWidget *widget,gpointer data);

//Quit application
void quit(GtkWidget *widget,gpointer data);

//Callback function of "config" menuitem
void config_activate(GtkWidget *widget,gpointer data);

//Callback function of "config1" menuitem
void config1_activate(GtkWidget *widget,gpointer data);

//InputBox:Input content and write the content to specificed file
void InputBox(const gchar *content,const char *filename);

//A callback function of entry "activate" signal
void entry_activate(GtkWidget *widget,gpointer data);

//MsgBox:Show Message and use a specific title
void MsgBox(const gchar *title,const gchar *msg);

//Callback function of "config2" menuitem
void config2_activate(GtkWidget *widget,gpointer data);

//Callback function of "about" menuitem
void about_activate(GtkWidget *widget,gpointer data);
