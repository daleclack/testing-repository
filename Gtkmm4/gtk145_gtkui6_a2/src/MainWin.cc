#include "MainWin.hh"
#include "jsonfile.hh"

WinShown curr_win;

MainWin::MainWin()
    : main_box(Gtk::Orientation::VERTICAL),
      btn_box(Gtk::Orientation::HORIZONTAL),
      btn_main("Main"),
      btn_win1("Win1"),
      btn_win2("Win2"),
      label1(" ")
{
    // Initalize window
    set_icon_name("org.gtk.daleclack");
    set_default_size(1024, 576);

    // Add popover menu bar
    //menu_bar = new Gtk::PopoverMenuBar(model_default);
    main_box.append(*(menu_bar.menubar));
    // (menu_bar.menubar)->show();

    // Add context menu
    // Gesture for right click
    gesture_right = Gtk::GestureClick::create();
    gesture_right->set_button(GDK_BUTTON_SECONDARY);
    gesture_right->signal_pressed().connect(sigc::mem_fun(*this, &MainWin::press));
    overlay1.add_controller(gesture_right);
    
    // The Context menu
    context_builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/context_menu.xml");
    auto gmenu = context_builder->get_object<Gio::MenuModel>("context_menu");
    context_menu.set_menu_model(gmenu);
    context_menu.set_parent(overlay1);
    context_menu.set_has_arrow(false);

    // Signal for context menu
    add_action("main_about", sigc::mem_fun(*this, &MainWin::main_about));
    add_action("custom", sigc::mem_fun(*this, &MainWin::prefs_activated));

    // Add a label
    label1.set_expand();
    label1.set_halign(Gtk::Align::FILL);
    label1.set_valign(Gtk::Align::FILL);
    main_box.append(label1);

    // Add buttons
    btn_box.append(btn_main);
    btn_box.append(btn_win1);
    btn_box.append(btn_win2);
    btn_box.set_halign(Gtk::Align::CENTER);
    btn_box.set_valign(Gtk::Align::END);
    main_box.append(btn_box);

    // Add widgets to the window
    main_box.set_halign(Gtk::Align::FILL);
    main_box.set_valign(Gtk::Align::FILL);
    overlay1.add_overlay(main_box);
    set_child(overlay1);
}

void MainWin::press(int n_press, double x, double y){
    // g_print("%f %f\n", x, y);
    // Show the context menu and the pointer position
    Gdk::Rectangle point(x, y, 1, 1);
    context_menu.set_pointing_to(point);
    context_menu.popup();
}

void MainWin::main_about(){
    
}

void MainWin::prefs_activated(){
    prefs_win.show();
}
