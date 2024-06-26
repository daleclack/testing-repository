#include "MyWindow.h"
#include "MyImage.h"
#include "img7.xpm"

struct _MyWindow{
    GtkApplicationWindow parent_instance;
    GtkWidget * img_view;
};

G_DEFINE_TYPE(MyWindow,my_window,GTK_TYPE_APPLICATION_WINDOW)

static void dialog_respone(GtkNativeDialog * dialog,int response,MyWindow * window){
    if(response == GTK_RESPONSE_ACCEPT){
        //Get Filename
        GFile * file = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(dialog));
        char * filename = g_file_get_path(file);

        GError * err = NULL;
        GdkPixbuf * pixbuf = gdk_pixbuf_new_from_file(filename,&err);
        if(err!=NULL){
            fprintf(stderr, "Unable to read file: %s\n", err->message);
            g_error_free(err);
        }else{
            my_image_set_pixbuf(MY_IMAGE(window->img_view),pixbuf);
        }

        g_object_unref(file);
        g_free(filename);
    }
    gtk_native_dialog_destroy(dialog);
}

static void openfile_dialog(GtkWidget * widget,MyWindow * window){
    //Create a dialog
    GtkFileChooserNative * dialog = gtk_file_chooser_native_new("Open Image File",GTK_WINDOW(window),
                                    GTK_FILE_CHOOSER_ACTION_OPEN,"OK","Cancel");

    //Link the "response" signal of dialog
    g_signal_connect(dialog,"response",G_CALLBACK(dialog_respone),window);

    gtk_native_dialog_show(GTK_NATIVE_DIALOG(dialog));
}

static void my_window_init(MyWindow * window){
    GtkWidget * vbox, * sw, * scale, * btnbox, * btnopen;
    
    //Initalize window
    gtk_window_set_default_size(GTK_WINDOW(window),800,450);
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");

    //Create Child widgets
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
    btnbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    sw = gtk_scrolled_window_new();

    //Add the image widget
    window->img_view = my_image_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(sw),window->img_view);
    gtk_widget_set_vexpand(sw,TRUE);
    gtk_box_append(GTK_BOX(vbox),sw);
    my_image_bind_adjustments(MY_IMAGE(window->img_view),
                              gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(sw)),
                              gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(sw)));

    //Add a scale
    scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,0.01,10.0,0.1);
    gtk_range_set_value(GTK_RANGE(scale),1.0);
    gtk_widget_set_hexpand(scale,TRUE);
    gtk_box_append(GTK_BOX(btnbox),scale);

    //Add a button
    btnopen = gtk_button_new_with_label("Open Image");
    g_signal_connect(btnopen,"clicked",G_CALLBACK(openfile_dialog),window);
    gtk_box_append(GTK_BOX(btnbox),btnopen);
    gtk_box_append(GTK_BOX(vbox),btnbox);

    //Bind the "value" property
    g_object_bind_property(gtk_range_get_adjustment(GTK_RANGE(scale)),"value",
                                                    window->img_view,"scale",
                                                    G_BINDING_BIDIRECTIONAL);

    //Default Image
    GdkPixbuf * pixbuf = gdk_pixbuf_new_from_xpm_data(img7);
    my_image_set_pixbuf(MY_IMAGE(window->img_view),pixbuf);
    g_object_unref(pixbuf);

    gtk_window_set_child(GTK_WINDOW(window),vbox);
}

static void my_window_class_init(MyWindowClass * klass){}

MyWindow * my_window_new(GtkApplication * application){
    return (MyWindow*)g_object_new(my_window_get_type(),"application",application,NULL);
}
