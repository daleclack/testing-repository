#include "MyMsgBox.h"

struct _MyMsgBox
{
    GtkWindow parent_instance;
    GtkWidget *main_box, *btn_box;
    GtkWidget *msg_label, *label1, *label2;
    GtkWidget *label3, *btn_ok;
};

G_DEFINE_TYPE(MyMsgBox, my_msgbox, GTK_TYPE_WINDOW)

void my_msgbox_show(MyMsgBox *msg_box, const char *message)
{
    // Set the label of message box
    gtk_label_set_label(GTK_LABEL(msg_box->msg_label), message);
    gtk_window_present(GTK_WINDOW(msg_box));
}

void btnok_clicked(GtkWidget *widget, MyMsgBox *msg_box)
{
    // Close the window
    gtk_window_destroy(GTK_WINDOW(msg_box));
}

static void my_msgbox_init(MyMsgBox *self)
{
    // Initalize window
    gtk_window_set_default_size(GTK_WINDOW(self), 300, 150);
    gtk_window_set_title(GTK_WINDOW(self), "Message");

    // Create widgets
    self->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    self->btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    // Create labels
    self->label1 = gtk_label_new(" ");
    self->msg_label = gtk_label_new(" ");
    self->label2 = gtk_label_new(" ");
    gtk_widget_set_vexpand(self->label1, TRUE);
    gtk_widget_set_vexpand(self->label2, TRUE);
    gtk_widget_set_halign(self->msg_label, GTK_ALIGN_CENTER);

    // Create label for spacing
    self->label3 = gtk_label_new(" ");
    gtk_widget_set_hexpand(self->label3, TRUE);
    gtk_widget_set_halign(self->label3, GTK_ALIGN_FILL);

    // Create "OK" Button
    self->btn_ok = gtk_button_new_with_label("OK");
    g_signal_connect(self->btn_ok, "clicked", G_CALLBACK(btnok_clicked), self);
    gtk_widget_set_halign(self->btn_ok, GTK_ALIGN_END);
    gtk_widget_set_hexpand(self->btn_box, TRUE);
    gtk_widget_set_halign(self->btn_box, GTK_ALIGN_FILL);

    // Pack widgets
    gtk_box_append(GTK_BOX(self->btn_box), self->label3);
    gtk_box_append(GTK_BOX(self->btn_box), self->btn_ok);
    gtk_box_append(GTK_BOX(self->main_box), self->label1);
    gtk_box_append(GTK_BOX(self->main_box), self->msg_label);
    gtk_box_append(GTK_BOX(self->main_box), self->label2);
    gtk_box_append(GTK_BOX(self->main_box), self->btn_box);

    // Set Margins
    gtk_widget_set_margin_bottom(self->main_box, 10);
    gtk_widget_set_margin_end(self->main_box, 10);
    gtk_widget_set_margin_start(self->main_box, 10);
    gtk_widget_set_margin_top(self->main_box, 10);

    gtk_window_set_child(GTK_WINDOW(self), self->main_box);
}

static void my_msgbox_class_init(MyMsgBoxClass *klass)
{
}

MyMsgBox *my_msgbox_new(GtkWindow *parent)
{
    return MY_MSGBOX(g_object_new(my_msgbox_get_type(),
                                  "transient-for", parent, NULL));
}
