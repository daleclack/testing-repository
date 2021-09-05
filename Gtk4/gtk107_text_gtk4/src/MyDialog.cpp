#include "MyDialog.h"
#include "../text_types.h"

static void my_dialog_response(GtkDialog *dialog,int response_id){
    GtkFileChooserAction action=gtk_file_chooser_get_action(GTK_FILE_CHOOSER(dialog));
    if(response_id == GTK_RESPONSE_OK){
        GtkWindow *win=gtk_window_get_transient_for(GTK_WINDOW(dialog));
        GFile *file=gtk_file_chooser_get_file(GTK_FILE_CHOOSER(dialog));
        switch(action){
            case GTK_FILE_CHOOSER_ACTION_OPEN:
                my_window_open(MY_WINDOW(win),file);
                break;
            case GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER:
                break;
            case GTK_FILE_CHOOSER_ACTION_SAVE:
                break;
        }
        g_object_unref(file);
    }
    gtk_window_destroy(GTK_WINDOW(dialog));
}

void my_dialog_new(MyWindow *window,const char *title,GtkFileChooserAction action){
    //Initalize window
    GtkWidget *dialog=gtk_file_chooser_dialog_new(title,GTK_WINDOW(window),
                    action,"OK",GTK_RESPONSE_OK,"Cancel",GTK_RESPONSE_CANCEL,NULL);
    
    g_signal_connect(dialog,"response",G_CALLBACK(my_dialog_response),NULL);

    gtk_window_present(GTK_WINDOW(dialog));
}

