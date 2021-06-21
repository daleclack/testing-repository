#include "MyDialog.h"
#include <cstdio>

struct _MyDialog{
    GtkDialog parent;
    GtkWidget *test_entry;
    const char *filename;
};

G_DEFINE_TYPE(MyDialog,my_dialog,GTK_TYPE_DIALOG)

static void entry_response(GtkWidget *widget,GtkDialog *dialog){
    gtk_dialog_response(dialog,GTK_RESPONSE_OK);
}

static void my_dialog_init(MyDialog *dialog){
    GtkWidget *content_area,*label;
    //Initalize Dialog
    gtk_window_set_icon_name(GTK_WINDOW(dialog),"org.gtk.daleclack");
    gtk_window_set_default_size(GTK_WINDOW(dialog),300,150);
    gtk_dialog_add_buttons(GTK_DIALOG(dialog),"OK",GTK_RESPONSE_OK,"Cancel",GTK_RESPONSE_CANCEL,NULL);
    //Get Content Area and add widgets
    content_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    label=gtk_label_new(" ");
    gtk_container_add(GTK_CONTAINER(content_area),label);
    label=gtk_label_new("Input Text:");
    gtk_container_add(GTK_CONTAINER(content_area),label);
    dialog->test_entry=gtk_entry_new();
    g_signal_connect(dialog->test_entry,"activate",G_CALLBACK(entry_response),dialog);
    gtk_entry_set_text(GTK_ENTRY(dialog->test_entry),"Test1");
    gtk_container_add(GTK_CONTAINER(content_area),dialog->test_entry);
}

static void dialog_response(GtkDialog *dialog,int response){
    //Get Text at response
    const char *content=gtk_entry_get_text(GTK_ENTRY(MY_DIALOG(dialog)->test_entry));
    const char *filename=MY_DIALOG(dialog)->filename;
    freopen(filename,"a",stdout);
    g_print("%s\n",content);
    fclose(stdout);
    gtk_widget_destroy(GTK_WIDGET(dialog));
}

static void my_dialog_class_init(MyDialogClass *class1){
    GTK_DIALOG_CLASS(class1)->response=dialog_response;
}

void set_filename(MyDialog *dialog,const char *filename){
    dialog->filename=filename;
}

MyDialog * my_dialog_new(){
    return MY_DIALOG(g_object_new(MY_DIALOG_TYPE,NULL));
}
