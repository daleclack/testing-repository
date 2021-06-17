#include <gtk/gtk.h>

static GtkWidget *infobar;
static GtkTextBuffer *textbuffer;

void dialog_response(GtkWidget *widget,int response,gpointer data){
    char *contents,*filename;
    gsize length;
    if(response==GTK_RESPONSE_OK){
        GFile *file=gtk_file_chooser_get_file((GtkFileChooser*)widget);
        filename=g_file_get_path(file);
        if(g_file_get_contents(filename,&contents,&length,NULL)){
            gtk_text_buffer_set_text(textbuffer,contents,length);
        }
        g_object_unref(file);
        g_free(contents);
        g_free(filename);
    }
    gtk_widget_destroy(widget);
}

void openfile_dialog(GtkWidget *widget,GtkWindow *parent){
    GtkFileChooserAction action=GTK_FILE_CHOOSER_ACTION_OPEN;
    GtkWidget *dialog=gtk_file_chooser_dialog_new("Open a text file",parent,
                      action,"OK",GTK_RESPONSE_OK,"Cancel",GTK_RESPONSE_CANCEL,NULL);

    GtkFileFilter *filter=gtk_file_filter_new();
    gtk_file_filter_set_name(filter,"Text Files");
    gtk_file_filter_add_mime_type(filter,"text/*");
    gtk_file_chooser_add_filter((GtkFileChooser*)dialog,filter);
    //g_object_unref(filter);

    filter=gtk_file_filter_new();
    gtk_file_filter_set_name(filter,"Any Files");
    gtk_file_filter_add_pattern(filter,"*");
    gtk_file_chooser_add_filter((GtkFileChooser*)dialog,filter);
    //g_object_unref(filter);

    g_signal_connect(dialog,"response",G_CALLBACK(dialog_response),NULL);
    gtk_widget_show_all(dialog);
}

void textbuffer_clear(GtkWidget *widget,GtkTextBuffer *buffer){
    gtk_text_buffer_set_text(buffer,"",-1);
    gtk_widget_show(infobar);
}

void infobar_response(GtkWidget *widget,gpointer data){
    gtk_widget_hide(widget);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    //Initalize window
    GtkWidget *window,*vbox;
    window=gtk_application_window_new(app);
    gtk_window_set_title((GtkWindow*)window,"Simple Text Editor");
    gtk_window_set_icon_name((GtkWindow*)window,"org.gtk.daleclack");
    gtk_window_set_default_size((GtkWindow*)window,800,450);
    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,5);

    //Initalize infobar
    infobar=gtk_info_bar_new_with_buttons("OK",GTK_RESPONSE_OK,NULL);
    GtkWidget *content_area=gtk_info_bar_get_content_area((GtkInfoBar*)infobar);
    GtkWidget *label=gtk_label_new("Cleared the text");
    g_signal_connect(infobar,"response",G_CALLBACK(infobar_response),NULL);
    gtk_container_add((GtkContainer*)content_area,label);
    gtk_box_pack_start((GtkBox*)vbox,infobar,TRUE,FALSE,0);

    //Ininalize TextView
    GtkWidget *scrolled;
    GtkWidget *textview;
    //GtkTextBuffer *textbuffer;
    scrolled=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy((GtkScrolledWindow*)scrolled,
                                  GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    textview=gtk_text_view_new();
    textbuffer=gtk_text_view_get_buffer((GtkTextView*)textview);
    gtk_widget_set_size_request(scrolled,800,440);
    gtk_container_add((GtkContainer*)scrolled,textview);
    gtk_box_pack_start((GtkBox*)vbox,scrolled,TRUE,TRUE,0);

    //Add Buttons
    GtkWidget *btn_box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    GtkWidget *btnopen,*btnclear,*btnexit;
    btnopen=gtk_button_new_with_label("Open File");
    g_signal_connect(btnopen,"clicked",G_CALLBACK(openfile_dialog),window);
    btnclear=gtk_button_new_with_label("Clear");
    g_signal_connect(btnclear,"clicked",G_CALLBACK(textbuffer_clear),textbuffer);
    btnexit=gtk_button_new_with_label("Exit");
    g_signal_connect_swapped(btnexit,"clicked",G_CALLBACK(gtk_widget_destroy),window);
    gtk_box_pack_end((GtkBox*)btn_box,btnexit,FALSE,FALSE,0);
    gtk_box_pack_end((GtkBox*)btn_box,btnclear,FALSE,FALSE,0);
    gtk_box_pack_end((GtkBox*)btn_box,btnopen,FALSE,FALSE,0);
    gtk_box_pack_end((GtkBox*)vbox,btn_box,TRUE,FALSE,0);

    //Add widgets and show everything
    gtk_container_add((GtkContainer*)window,vbox);
    gtk_widget_show_all(window);
    gtk_widget_hide(infobar);
}

int main(int argc,char **argv){
    GtkApplication *app;
    app=gtk_application_new("org.gtk.daleclack",G_APPLICATION_NON_UNIQUE);
    g_signal_connect(app,"activate",G_CALLBACK(gtkmain),NULL);
    return g_application_run((GApplication*)app,argc,argv);
}