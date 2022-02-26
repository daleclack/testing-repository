#include "MyWin.hh"
#include "winpe.xpm"

MyWin::MyWin()
{
    int width, height;

    // Initalize Window
    set_icon_name("org.gtk.daleclack");
    set_title(_("Background Preferences Test"));

    prefs_win.get_winsize_config(width, height);

    // Add Background
    auto pixbuf = Gdk::Pixbuf::create_from_xpm_data(winpe);
    auto sized = pixbuf->scale_simple(width, height, Gdk::INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(m_back.gobj(), sized->gobj());
    pixbuf.reset();
    sized.reset();

    // Button for background
    btnback.set_label(_("Window Preferences"));
    btnback.set_halign(Gtk::ALIGN_CENTER);
    btnback.set_valign(Gtk::ALIGN_CENTER);
    btnback.set_relief(Gtk::RELIEF_NONE);
    m_overlay.add_overlay(btnback);
    btnback.signal_clicked().connect(sigc::mem_fun(*this, &MyWin::btnback_clicked));

    // Add widgets
    m_back.set_hexpand();
    m_back.set_vexpand();
    m_overlay.add(m_back);
    add(m_overlay);

    // Initalize MyPrefs
    prefs_win.set_background(&m_back);

    show_all_children();
}

void MyWin::btnback_clicked()
{
    prefs_win.show_all();
}
