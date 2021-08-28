#include "mywindow.h"

struct _MyWindow{
    GtkApplicationWindow parent;
};

typedef struct _MyWindowPrivate MyWindowPrivate;

struct _MyWindowPrivate{
    GSettings *settings;
    GtkWidget *stack;
    GtkWidget *search;
    GtkWidget *searchbar;
    GtkWidget *searchentry;
    GtkWidget *gears;
    GtkWidget *sidebar;
    GtkWidget *words;
    GtkWidget *lines;
    GtkWidget *lines_label;
};

G_DEFINE_TYPE_WITH_PRIVATE(MyWindow,my_window,GTK_TYPE_APPLICATION_WINDOW)

static void search_text_changed(GtkEntry *entry){
    MyWindow *win;
    MyWindowPrivate *priv;
    const gchar *text;
    GtkWidget *tab;
    GtkWidget *view;
    GtkTextBuffer *buffer;
    GtkTextIter start, match_start, match_end;

    text = gtk_entry_get_text (entry);

    if (text[0] == '\0')
        return;

    win = MY_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (entry)));
    priv = (MyWindowPrivate*)my_window_get_instance_private (win);

    tab = gtk_stack_get_visible_child (GTK_STACK (priv->stack));
    view = gtk_bin_get_child (GTK_BIN (tab));
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

    /* Very simple-minded search implementation */
    gtk_text_buffer_get_start_iter (buffer, &start);
    if (gtk_text_iter_forward_search (&start, text, GTK_TEXT_SEARCH_CASE_INSENSITIVE,
                                      &match_start, &match_end, NULL))
    {
        gtk_text_buffer_select_range (buffer, &match_start, &match_end);
        gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW (view), &match_start,
                                      0.0, FALSE, 0.0, 0.0);
    }

}

static void find_word(GtkButton *button,MyWindow *win)
{
    MyWindowPrivate *priv;
    const gchar *word;

    priv = (MyWindowPrivate*)my_window_get_instance_private (win);

    word = gtk_button_get_label (button);
    gtk_entry_set_text (GTK_ENTRY (priv->searchentry), word);
}

static void update_words(MyWindow *win){
    MyWindowPrivate *priv;
    GHashTable *strings;
    GHashTableIter iter;
    GtkWidget *tab, *view, *row;
    GtkTextBuffer *buffer;
    GtkTextIter start, end;
    GList *children, *l;
    gchar *word, *key;

    priv = (MyWindowPrivate*)my_window_get_instance_private (win);

    tab = gtk_stack_get_visible_child (GTK_STACK (priv->stack));

    if (tab == NULL)
        return;

    view = gtk_bin_get_child (GTK_BIN (tab));
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

    strings = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);

    gtk_text_buffer_get_start_iter (buffer, &start);
    while (!gtk_text_iter_is_end (&start))
    {
        while (!gtk_text_iter_starts_word (&start))
        {
            if (!gtk_text_iter_forward_char (&start))
                goto done;
        }
        end = start;
        if (!gtk_text_iter_forward_word_end (&end))
            goto done;
        word = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
        g_hash_table_add (strings, g_utf8_strdown (word, -1));
        g_free (word);
        start = end;
    }

done:
    children = gtk_container_get_children (GTK_CONTAINER (priv->words));
    for (l = children; l; l = l->next)
        gtk_container_remove (GTK_CONTAINER (priv->words), GTK_WIDGET (l->data));
    g_list_free (children);

    g_hash_table_iter_init (&iter, strings);
    while (g_hash_table_iter_next (&iter, (gpointer *)&key, NULL))
        {
        row = gtk_button_new_with_label (key);
        g_signal_connect (row, "clicked",
                            G_CALLBACK (find_word), win);
        gtk_widget_show (row);
        gtk_container_add (GTK_CONTAINER (priv->words), row);
        }

    g_hash_table_unref (strings);
}

static void update_lines(MyWindow *win){
    MyWindowPrivate *priv;
    GtkWidget *tab,*view;
    GtkTextBuffer *buffer;
    GtkTextIter iter;
    int count;
    gchar *lines;

    //Get Private member
    priv=(MyWindowPrivate*)my_window_get_instance_private(win);

    tab = gtk_stack_get_visible_child (GTK_STACK (priv->stack));

    if(tab==NULL){
        return ;
    }

    view = gtk_bin_get_child (GTK_BIN (tab));
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

    count=0;

    gtk_text_buffer_get_start_iter (buffer, &iter);
    while (!gtk_text_iter_is_end (&iter))
    {
        count++;
        if (!gtk_text_iter_forward_line (&iter))
            break;
    }

    lines=g_strdup_printf("%d",count);
    gtk_label_set_label(GTK_LABEL(priv->lines),lines);
    g_free(lines);
}


static void visible_child_changed(GObject *stack,GParamSpec *pspec){
    MyWindow *win;
    MyWindowPrivate *priv;

    if(gtk_widget_in_destruction(GTK_WIDGET(stack))){
        return ;
    }

    win=MY_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(stack)));
    priv=(MyWindowPrivate*)my_window_get_instance_private(win);
    gtk_search_bar_set_search_mode (GTK_SEARCH_BAR (priv->searchbar), FALSE);
    update_words(win);
    update_lines(win);
}

static void word_changed(GObject *sidebar,GParamSpec *pspec,MyWindow *win){
    update_words(win);
}

static void my_window_init(MyWindow *window){
    //Inintalize Window
    GtkBuilder *builder;
    GMenuModel *app_menu;
    MyWindowPrivate * priv;
    GAction *action;

    priv=(MyWindowPrivate*)my_window_get_instance_private(window);
    gtk_widget_init_template(GTK_WIDGET(window));

    //Add Menu
    builder=gtk_builder_new_from_resource("/org/gtk/daleclack/app-menu.ui");
    app_menu=G_MENU_MODEL(gtk_builder_get_object(builder,"appmenu"));
    gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(priv->gears),app_menu);
    g_object_unref(builder);

    //Bind Settings
    priv->settings=g_settings_new("org.gtk.daleclack");

    g_settings_bind (priv->settings, "transition",
                     priv->stack, "transition-type",
                     G_SETTINGS_BIND_DEFAULT);
                     
    //Bind Search Button and searchbar
    g_object_bind_property(priv->search, "active",
                           priv->searchbar, "search-mode-enabled",
                           G_BINDING_BIDIRECTIONAL);

    g_settings_bind (priv->settings, "show-words",
                     priv->sidebar, "reveal-child",
                     G_SETTINGS_BIND_DEFAULT);

    action = (GAction*) g_property_action_new ("show-lines", priv->lines, "visible");
    g_action_map_add_action (G_ACTION_MAP  (window), action);
    g_object_unref (action);

    g_object_bind_property (priv->lines, "visible",
                            priv->lines_label, "visible",
                            G_BINDING_DEFAULT);

    g_signal_connect(priv->sidebar,"notify::reveal-child",
                    G_CALLBACK(word_changed),window);
    
    action = g_settings_create_action (priv->settings, "show-words");
    g_action_map_add_action (G_ACTION_MAP (window), action);
    g_object_unref (action);

    g_object_bind_property (priv->lines, "visible",
                            priv->lines_label, "visible",
                            G_BINDING_DEFAULT);
}

static void my_window_dispose (GObject *object)
{
    //Free Memory for settings
    MyWindowPrivate *priv;
    MyWindow *win;

    win=MY_WINDOW(object);
    priv = (MyWindowPrivate*)my_window_get_instance_private(win);
    g_clear_object (&priv->settings);

    G_OBJECT_CLASS (my_window_parent_class)->dispose (object);
}


static void my_window_class_init(MyWindowClass *class1){
    //Inintalize Window
    G_OBJECT_CLASS (class1)->dispose = my_window_dispose;


    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class1),
                                                "/org/gtk/daleclack/window.ui");
    gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class1),MyWindow,stack);
    gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class1),MyWindow,search);
    gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class1),MyWindow,searchbar);
    gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class1),MyWindow,searchentry);
    gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class1),MyWindow,gears);
    gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class1),MyWindow,sidebar);
    gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class1),MyWindow,words);
    gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class1),MyWindow,lines);
    gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class1),MyWindow,lines_label);

    gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(class1), search_text_changed);
    gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(class1), visible_child_changed);
}

MyWindow * my_window_new(MyApp *app){
    return (MyWindow*)g_object_new(MY_WINDOW_TYPE,"application",app,NULL);
}

void my_window_open(MyWindow *window,GFile *file){
    MyWindowPrivate * priv;
    gchar * basename, * contents;
    GtkWidget * scrolled, * view;
    gsize length;
    GtkTextBuffer *buffer;
    GtkTextTag *tag;
    GtkTextIter start_iter,end_iter;

    //Get Stack and basename of file
    priv=(MyWindowPrivate*)my_window_get_instance_private(window);
    basename=g_file_get_basename(file);

    //Create Text View
    scrolled = gtk_scrolled_window_new (NULL, NULL);
    gtk_widget_show (scrolled);
    gtk_widget_set_hexpand (scrolled, TRUE);
    gtk_widget_set_vexpand (scrolled, TRUE);
    view = gtk_text_view_new ();
    gtk_text_view_set_editable (GTK_TEXT_VIEW (view), FALSE);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view), FALSE);
    gtk_widget_show (view);
    gtk_container_add (GTK_CONTAINER (scrolled), view);
    gtk_stack_add_titled (GTK_STACK (priv->stack), scrolled, basename, basename);

    //buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

    //Load Contents and get buffer
    if (g_file_load_contents (file, NULL, &contents, &length, NULL, NULL))
    {
        buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
        gtk_text_buffer_set_text (buffer, contents, length);
        g_free (contents);
    }

    //Text Tag
    tag=gtk_text_buffer_create_tag(buffer,NULL,NULL);
    g_settings_bind(priv->settings,"font",tag,"font",G_SETTINGS_BIND_DEFAULT);
    gtk_text_buffer_get_start_iter(buffer,&start_iter);
    gtk_text_buffer_get_end_iter(buffer,&end_iter);
    gtk_text_buffer_apply_tag(buffer,tag,&start_iter,&end_iter);

    g_free (basename);
    gtk_widget_set_sensitive(priv->search,TRUE);
    update_words (window);
    update_lines (window);
}
