#include "MyWin.hh"
#include "winpe.xpm"

MyWin::MyWin(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade)
    : Gtk::Window(cobject),
      ref_builder(ref_Glade)
{
    // Initalize window
    set_icon_name("org.gtk.daleclack");

    // Get Widgets
    ref_builder->get_widget("main_overlay", main_overlay);
    ref_builder->get_widget("main_stack", main_stack);
    ref_builder->get_widget("start_page", start_page);
    ref_builder->get_widget("launchpad_page", launchpad_page);
    ref_builder->get_widget("background", background);
    ref_builder->get_widget("btnstart", btnstart);
    ref_builder->get_widget("btnback", btnback);

    // Initalize Background
    auto pixbuf = Gdk::Pixbuf::create_from_xpm_data(winpe);
    auto sized = pixbuf->scale_simple(800, 450, Gdk::INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(background->gobj(), sized->gobj());
    pixbuf.reset();
    sized.reset();

    // Add Overlay widget
    main_stack->set_halign(Gtk::ALIGN_FILL);
    main_stack->set_valign(Gtk::ALIGN_FILL);
    main_overlay->add_overlay(*main_stack);

    // Add style sheet
    provider = Gtk::CssProvider::create();
    provider->load_from_resource("/org/gtk/daleclack/style.css");
    auto context = launchpad_page->get_style_context();
    context->add_provider(provider,G_MAXUINT);

    // Link Signals
    btnback->signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnback_clicked));
    btnstart->signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnstart_clicked));

    show_all_children();
}

void MyWin::btnstart_clicked()
{
    main_stack->set_visible_child(*launchpad_page);
}

void MyWin::btnback_clicked()
{
    main_stack->set_visible_child(*start_page);
}

MyWin *MyWin::create()
{
    MyWin *window = nullptr;

    auto builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/main_stack.ui");
    builder->get_widget_derived("window", window);

    return window;
}
