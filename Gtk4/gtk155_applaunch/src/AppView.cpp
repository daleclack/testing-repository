#include "AppView.h"

// Create a model for application
static GListModel *create_app_model()
{
    GListStore *store;
    GList *apps, *temp;

    // Create a list contains the application info
    store = g_list_store_new(G_TYPE_APP_INFO);

    // Get Appication list
    apps = g_app_info_get_all();

    // Append apps item to the list
    for (temp = apps; temp; temp = temp->next)
    {
        g_list_store_append(store, temp->data);
    }

    g_list_free_full(apps, g_object_unref);

    return G_LIST_MODEL(store);
}

static void app_view_setup(GtkListItemFactory *factory, GtkListItem *item)
{
    GtkWidget *app_box, *image, *label;

    // Create widgets
    app_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    image = gtk_image_new();
    label = gtk_label_new("          ");
    gtk_image_set_pixel_size(GTK_IMAGE(image), 40);
    gtk_widget_set_size_request(label, 76, 12);
    gtk_label_set_ellipsize(GTK_LABEL(label), PANGO_ELLIPSIZE_END);

    // Append widgets to the box
    gtk_box_append(GTK_BOX(app_box), image);
    gtk_box_append(GTK_BOX(app_box), label);

    gtk_list_item_set_child(item, app_box);
}

static void app_view_bind(GtkListItemFactory *factory, GtkListItem *item)
{
    GtkWidget *image;
    GtkWidget *label;
    GAppInfo *app_info;

    // Get Widgets
    image = gtk_widget_get_first_child(gtk_list_item_get_child(item));
    label = gtk_widget_get_next_sibling(image);
    app_info = G_APP_INFO(gtk_list_item_get_item(item));

    // Initalize widgets
    GIcon *icon = g_app_info_get_icon(app_info);
    if(!icon)
    {
        gtk_image_set_from_icon_name(GTK_IMAGE(image), "application-x-executable");
    }else{
        gtk_image_set_from_gicon(GTK_IMAGE(image), g_app_info_get_icon(app_info));
    }
    gtk_label_set_label(GTK_LABEL(label), g_app_info_get_display_name(app_info));
}

static void app_view_activate(GtkGridView *list, guint position, gpointer data)
{
    GAppInfo *app_info;
    GdkAppLaunchContext *context;
    GError *error = NULL;

    app_info = G_APP_INFO(g_list_model_get_item(G_LIST_MODEL(gtk_grid_view_get_model(list)),
                                                position));

    /* Prepare the context for launching the application and launch it. This
     * code is explained in detail in the documentation for GdkAppLaunchContext
     * and GAppInfo.
     */
    context = gdk_display_get_app_launch_context(gtk_widget_get_display(GTK_WIDGET(list)));
    if (!g_app_info_launch(app_info,
                           NULL,
                           G_APP_LAUNCH_CONTEXT(context),
                           &error))
    {
        // GtkAlertDialog *dialog;

        // /* And because error handling is important, even a simple demo has it:
        //  * We display an error dialog that something went wrong.
        //  */
        // dialog = gtk_alert_dialog_new("Could not launch %s", g_app_info_get_display_name(app_info));
        // gtk_alert_dialog_set_detail(dialog, error->message);
        // gtk_alert_dialog_show(dialog, GTK_WINDOW(gtk_widget_get_root(GTK_WIDGET(list))));
        // g_object_unref(dialog);
        // g_clear_error(&error);
    }

    g_object_unref(context);
    g_object_unref(app_info);
}

GtkWidget *app_view_new()
{
    GtkWidget *list, *sw;
    GListModel *model;
    GtkListItemFactory *factory;

    // Create widgets
    sw = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw),
                                   GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

    // Create list item factory
    factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", G_CALLBACK(app_view_setup), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(app_view_bind), NULL);

    // Create model and view
    model = create_app_model();
    list = gtk_grid_view_new(GTK_SELECTION_MODEL(
                             gtk_single_selection_new(model)),
                             factory);
    g_signal_connect(list, "activate", G_CALLBACK(app_view_activate), NULL);
    gtk_grid_view_set_min_columns(GTK_GRID_VIEW(list), 8);

    // Add Child
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(sw), list);

    return sw;
}
