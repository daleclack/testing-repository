#include "MyDialog.h"

struct _MyDialog{
    GtkDialog parent;
    GtkWidget *test_entry;
};

G_DEFINE_TYPE(MyDialog,my_dialog,GTK_TYPE_DIALOG)

static void my_dialog_init(MyDialog *dialog){
    GtkWidget *content_area,*label;
    //Initalize Dialog
    gtk_window_set_icon_name((GtkWindow*)dialog,"org.gtk.daleclack");
    gtk_window_set_default_size((GtkWindow*)dialog,300,150);
    gtk_dialog_add_buttons((GtkDialog*)dialog,"OK",GTK_RESPONSE_OK,"Cancel",GTK_RESPONSE_CANCEL,NULL);
    //Get Content Area and add widgets
    content_area=gtk_dialog_get_content_area((GtkDialog*)dialog);
    label=gtk_label_new(" ");
    gtk_container_add((GtkContainer*)content_area,label);
    label=gtk_label_new("Input Text:");
    gtk_container_add((GtkContainer*)content_area,label);
    dialog->test_entry=gtk_entry_new();
    gtk_entry_set_text((GtkEntry*)dialog->test_entry,"Test1");
    gtk_container_add((GtkContainer*)content_area,dialog->test_entry);
}

static void dialog_response(GtkDialog *dialog,int response){
    //Get Text at response
    const char *content=gtk_entry_get_text(GTK_ENTRY(MY_DIALOG(dialog)->test_entry));
    g_print("%s\n",content);
    gtk_widget_destroy((GtkWidget*)dialog);
}

static void my_dialog_class_init(MyDialogClass *class1){
    GTK_DIALOG_CLASS(class1)->response=dialog_response;
}

MyDialog * my_dialog_new(){
    return (MyDialog*)g_object_new(MY_DIALOG_TYPE,NULL);
}
