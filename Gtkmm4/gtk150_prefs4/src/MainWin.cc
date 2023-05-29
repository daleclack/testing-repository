#include "MainWin.hh"
#include "MyPrefs.hh"
#include "winpe.xpm"

MainWin::MainWin(){
    // Initalize window
    set_default_size(1024, 576);
    set_icon_name("org.gtk.daleclack");

    // Set default background
    m_background.set_expand();
    auto pixbuf = Gdk::Pixbuf::create_from_xpm_data(winpe);
    auto sized = pixbuf->scale_simple(1024, 576, Gdk::InterpType::BILINEAR);
    m_background.set_pixbuf(sized);
    pixbuf.reset();
    sized.reset();

    // Add Gesture
    right_click = Gtk::GestureClick::create();
    m_overlay.add_controller(right_click);
    right_click->set_button(GDK_BUTTON_SECONDARY);
    right_click->signal_pressed().connect(sigc::mem_fun(*this, &MainWin::pressed));

    // Initalize menu
    menu_builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/mainmenu.xml");
    auto model = menu_builder->get_object<Gio::MenuModel>("model");
    context_menu.set_menu_model(model);
    context_menu.set_parent(m_overlay);
    context_menu.set_has_arrow(false);

    // Add widgets
    m_overlay.set_child(m_background);
    set_child(m_overlay);
}

void MainWin::pressed(int n_click, double x, double y){
    // Show the context menu on the position of mouse
    context_menu.set_pointing_to(Gdk::Rectangle(x, y, 1, 1));
    context_menu.popup();
}

