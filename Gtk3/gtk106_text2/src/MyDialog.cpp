#include "MyDialog.h"
#include "../text_types.h"

struct _MyDialog{
    GtkFileChooserDialog parent;
};

G_DEFINE_TYPE(MyDialog,my_dialog,GTK_TYPE_FILE_CHOOSER_DIALOG)

static void my_dialog_response(GtkDialog *dialog,int response_id){
    if(response_id == GTK_RESPONSE_OK){
        GtkWindow *win=gtk_window_get_transient_for(GTK_WINDOW(dialog));
        GFile *file=gtk_file_chooser_get_file(GTK_FILE_CHOOSER(dialog));
        my_window_open(MY_WINDOW(win),file);
        g_object_unref(file);
    }
    gtk_widget_destroy(GTK_WIDGET(dialog));
}

static void my_dialog_init(MyDialog * dialog){
    //Initalize window
    gtk_window_set_title(GTK_WINDOW(dialog),"Open a text file");
    gtk_dialog_add_buttons(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK,"Cancel",GTK_RESPONSE_CANCEL,NULL);
}

static void my_dialog_class_init(MyDialogClass *dlgclass){
    GTK_DIALOG_CLASS(dlgclass)->response=my_dialog_response;
}

MyDialog * my_dialog_new(MyWindow * window){
    return (MyDialog*)g_object_new(MY_DIALOG_TYPE,"transient-for",window,NULL);
}
