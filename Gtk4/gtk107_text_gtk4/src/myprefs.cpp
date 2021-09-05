#include "myapplication.h"
#include "myprefs.h"

struct _MyPrefs{
    GtkDialog parent;
    GSettings *settings;
    GtkWidget *font;
    GtkWidget *transition;
};

G_DEFINE_TYPE(MyPrefs,my_prefs,GTK_TYPE_DIALOG)

static void my_prefs_init(MyPrefs *dialog){
    gtk_widget_init_template(GTK_WIDGET(dialog));
    dialog->settings=g_settings_new("org.gtk.daleclack");

    //Bind Proprties
    g_settings_bind(dialog->settings,"font",
                    dialog->font,"font",
                    G_SETTINGS_BIND_DEFAULT);

    g_settings_bind(dialog->settings,"transition",
                    dialog->transition,"active-id",
                    G_SETTINGS_BIND_DEFAULT);
}

static void my_prefs_dispose(GObject *object){
    //Free Memory
    g_clear_object(&MY_PREFS(object)->settings);

    G_OBJECT_CLASS(my_prefs_parent_class)->dispose(object);
}

static void my_prefs_class_init(MyPrefsClass *dlgclass){
    //Inintalize Dialog and get child
    G_OBJECT_CLASS(dlgclass)->dispose=my_prefs_dispose;

    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(dlgclass),
                                                "/org/gtk/daleclack/prefs.ui");
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(dlgclass),MyPrefs,font);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(dlgclass),MyPrefs,transition);
}

MyPrefs * my_prefs_new(MyWindow *win){
    return (MyPrefs*)g_object_new(MY_PREFS_TYPE, "transient-for", win, "use-header-bar", TRUE, NULL);
}
