#include "mywindow.h"
#include "MyDialog.h"
#include "myprefs.h"

struct _MyWindow{
    GtkApplicationWindow parent;
};

typedef struct _MyWindowPrivate MyWindowPrivate;

struct _MyWindowPrivate{
    GtkWidget * stack;
    GtkWidget * gears;
    GSettings * settings;
    GtkWidget * search;
    GtkWidget * searchbar;
};

G_DEFINE_TYPE_WITH_PRIVATE(MyWindow,my_window,GTK_TYPE_APPLICATION_WINDOW)

static void search_text_changed(GtkEntry *entry){
    MyWindow *win;
    MyWindowPrivate *priv;
    const char *text;
    GtkWidget *tab,*view;
    GtkTextBuffer *buffer;
    GtkTextIter start,march_start,march_end;

    text=gtk_entry_get_text(entry);
    if(text[0]=='\0'){
        return ;
    }
    
    win=MY_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(entry)));
    priv=(MyWindowPrivate*)my_window_get_instance_private(win);

    tab=gtk_stack_get_visible_child(GTK_STACK(priv->stack));
    view=gtk_bin_get_child(GTK_BIN(tab));
    buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    /* Very simple-minded search implementation */
    gtk_text_buffer_get_start_iter(buffer,&start);
    if(gtk_text_iter_forward_search(&start,text,GTK_TEXT_SEARCH_VISIBLE_ONLY
                                    ,&march_start,&march_end,NULL))
    {
        gtk_text_buffer_select_range(buffer,&march_start,&march_end);
        gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(view),&start,0.0,FALSE,0.0,0.0);
    }
}

static void visible_child_changed(GObject *stack,GParamSpec *pspec){
    MyWindow *win;
    MyWindowPrivate *priv;
    
    win=MY_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(stack)));

    priv=(MyWindowPrivate*)my_window_get_instance_private(win);
    gtk_search_bar_set_search_mode(GTK_SEARCH_BAR(priv->searchbar),FALSE);
}

static void open_dialog(GSimpleAction *action,
                        GVariant      *parmeter,
                        gpointer       data)    //Open the file dialog
{
    MyDialog *dialog;
    dialog=my_dialog_new(MY_WINDOW(data));
    gtk_window_present(GTK_WINDOW(dialog));
}

static void preferences_activated(GSimpleAction *action,
                                  GVariant      *parmeter,
                                  gpointer       data)
{
    MyPrefs * prefs;
    prefs=my_prefs_new(MY_WINDOW(data));
    gtk_window_present(GTK_WINDOW(prefs));
}

static void my_window_init(MyWindow *window){
    //Ininalize window
    gtk_widget_init_template(GTK_WIDGET(window));
    gtk_window_set_icon_name(GTK_WINDOW(window),"org.gtk.daleclack");

    //Add Actions
    static GActionEntry entries[]={
        {"open",open_dialog,NULL,NULL,NULL},
        {"preferences",preferences_activated,NULL,NULL,NULL}
    };
    g_action_map_add_action_entries(G_ACTION_MAP(window),entries,G_N_ELEMENTS(entries),window);

    //Get Private widgets
    MyWindowPrivate *priv;
    priv=(MyWindowPrivate*)my_window_get_instance_private(window);

    //Add Menu
    GtkBuilder * builder;
    GMenuModel * model;
    builder=gtk_builder_new_from_resource("/org/gtk/daleclack/app-menu.ui");
    model=G_MENU_MODEL(gtk_builder_get_object(builder,"appmenu"));
    gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(priv->gears),model);

    //Bind Settings
    priv->settings=g_settings_new("org.gtk.daleclack");
    g_settings_bind (priv->settings, "transition",
                     priv->stack, "transition-type",
                     G_SETTINGS_BIND_DEFAULT);

    g_object_bind_property(priv->search,"active",
                           priv->searchbar,"search-mode-enabled",
                           G_BINDING_BIDIRECTIONAL);
}

static void my_window_dispose(GObject *object){

    MyWindowPrivate *priv;
    priv=(MyWindowPrivate*)my_window_get_instance_private(MY_WINDOW(object));

    g_clear_object(&priv->settings);

    G_OBJECT_CLASS(my_window_parent_class)->dispose(object);
}

static void my_window_class_init(MyWindowClass *winclass){
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(winclass),
                                                "/org/gtk/daleclack/window.ui");

    G_OBJECT_CLASS(winclass)->dispose=my_window_dispose;

    //Get Child widgets
    gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(winclass),MyWindow,stack);
    gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(winclass),MyWindow,gears);
    gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(winclass),MyWindow,search);
    gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(winclass),MyWindow,searchbar);

    gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(winclass),search_text_changed);
    gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(winclass),visible_child_changed);
}

MyWindow * my_window_new(MyApplication *app){
    return (MyWindow*)g_object_new(MY_WINDOW_TYPE,"application",app,NULL);
}

void my_window_open(MyWindow *window,GFile *file){
    MyWindowPrivate *priv;
    char *basename;
    GtkWidget *scrolled, *view;
    char *contents;
    gsize length;
    GtkTextBuffer * buffer;
    GtkTextIter start,end;
    GtkTextTag * tag;

    //Get basename and stack
    priv=(MyWindowPrivate*)my_window_get_instance_private(window);
    basename=g_file_get_basename(file);

    scrolled=gtk_scrolled_window_new(NULL,NULL);
    gtk_widget_show (scrolled);
    gtk_widget_set_hexpand (scrolled, TRUE);
    gtk_widget_set_vexpand (scrolled, TRUE);
    view = gtk_text_view_new ();
    gtk_text_view_set_editable (GTK_TEXT_VIEW (view), FALSE);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view), FALSE);
    gtk_widget_show (view);
    gtk_container_add (GTK_CONTAINER (scrolled), view);
    gtk_stack_add_titled (GTK_STACK (priv->stack), scrolled, basename, basename);

    if (g_file_load_contents (file, NULL, &contents, &length, NULL, NULL))
    {
        buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
        gtk_text_buffer_set_text (buffer, contents, length);
        g_free (contents);
    }

    //Apply Tag
    tag=gtk_text_buffer_create_tag(buffer,NULL,NULL);
    g_settings_bind(priv->settings,"font",tag,"font",G_SETTINGS_BIND_DEFAULT);
    gtk_text_buffer_get_start_iter(buffer,&start);
    gtk_text_buffer_get_end_iter(buffer,&end);
    gtk_text_buffer_apply_tag(buffer,tag,&start,&end);

    g_free (basename);
}
