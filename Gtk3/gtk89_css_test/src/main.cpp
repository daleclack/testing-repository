#include <gtk/gtk.h>

static void apply_css (GtkWidget *widget, GtkStyleProvider *provider)
{
  gtk_style_context_add_provider (gtk_widget_get_style_context (widget), provider, G_MAXUINT);
  if (GTK_IS_CONTAINER (widget))
    gtk_container_forall (GTK_CONTAINER (widget), (GtkCallback) apply_css, provider);
}

static void gtkmain(GtkApplication *app,gpointer user_data){
    GtkWidget *window,*container,*child;
    window = gtk_application_window_new (app);
    GtkStyleProvider *provider;
    gtk_window_set_title (GTK_WINDOW (window), "CSS Accordion");
    gtk_window_set_default_size (GTK_WINDOW (window), 600, 300);

    container = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign (container, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (container, GTK_ALIGN_CENTER);
    gtk_container_add (GTK_CONTAINER (window), container);

    child = gtk_button_new_with_label ("This");
    gtk_container_add (GTK_CONTAINER (container), child);

    child = gtk_button_new_with_label ("Is");
    gtk_container_add (GTK_CONTAINER (container), child);

    child = gtk_button_new_with_label ("A");
    gtk_container_add (GTK_CONTAINER (container), child);

    child = gtk_button_new_with_label ("CSS");
    gtk_container_add (GTK_CONTAINER (container), child);

    child = gtk_button_new_with_label ("Accordion");
    gtk_container_add (GTK_CONTAINER (container), child);

    child = gtk_button_new_with_label (":-)");
    gtk_container_add (GTK_CONTAINER (container), child);

    provider = GTK_STYLE_PROVIDER (gtk_css_provider_new ());
    gtk_css_provider_load_from_resource (GTK_CSS_PROVIDER (provider), "/css_accordion/css_accordion.css");

    apply_css (window, provider);
    gtk_widget_show_all (window);
}

int main(int argc,char ** argv){
    GtkApplication *app = gtk_application_new ("org.gtk.daleclack", G_APPLICATION_NON_UNIQUE);
    g_signal_connect (app, "activate", G_CALLBACK (gtkmain), NULL);
    return g_application_run(G_APPLICATION (app), argc, argv);
}
