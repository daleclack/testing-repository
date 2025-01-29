#include "MainWin.hh"

MainWin::MainWin()
    : menu_box(Gtk::Orientation::HORIZONTAL, 5),
    dock_box(Gtk::Orientation::VERTICAL, 5),
    win1_button("w1"),
    win2_button("w2")
{
    // Initalize main window
    set_default_size(800, 450);
    set_title("Test1 for My Gtk UI 8");

    // Add widgets
    menu_box.set_valign(Gtk::Align::START);
    menu_box.set_hexpand(true);
    overlay.add_overlay(menu_box);

    dock_box.append(win1_button);
    dock_box.append(win2_button);
    dock_box.set_halign(Gtk::Align::START);
    dock_box.set_valign(Gtk::Align::CENTER);
    overlay.add_overlay(dock_box);

    // Add main menu
    main_builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/main_menu.xml");
    auto menu = main_builder->get_object<Gio::MenuModel>("main_menu");
    global_menu.set_menu_model(menu);
    menu_box.append(global_menu);

    // Set child windows
    win1.set_transient_for(*this);
    win2.set_transient_for(*this);

    // Add signals
    win1_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWin::btnwin1_clicked));
    win2_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWin::btnwin2_clicked));

    // Add overlay to the main window
    set_child(overlay);
}

void MainWin::btnwin1_clicked()
{
    win1.present();
}

void MainWin::btnwin2_clicked()
{
    win2.present();
}

MainWin::~MainWin()
{
}