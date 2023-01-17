#include "MenuWin.hh"
#include "Win1.hh"
#include "Win2.hh"
#include "jsonfile.hh"

WinShown curr_win;

MenuWin::MenuWin()
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

    // Add actions
    add_action("new_win1", sigc::mem_fun(*this, &MenuWin::new_win1));
    add_action("quit_win1", sigc::mem_fun(*this, &MenuWin::quit_win1));
    add_action("new_win2", sigc::mem_fun(*this, &MenuWin::new_win2));
    add_action("quit_win2", sigc::mem_fun(*this, &MenuWin::quit_win2));
    add_action("about_win1", sigc::mem_fun(*this, &MenuWin::show_about_win1));
    add_action("about_win2", sigc::mem_fun(*this, &MenuWin::show_about_win2));

    // Add popover menu bar
    //menu_bar = new Gtk::PopoverMenuBar(model_default);
    main_box.append(*(menu_bar.menubar));
    // (menu_bar.menubar)->show();

    // Add context menu
    // Gesture for right click
    gesture_right = Gtk::GestureClick::create();
    gesture_right->set_button(GDK_BUTTON_SECONDARY);
    gesture_right->signal_pressed().connect(sigc::mem_fun(*this, &MenuWin::press));
    overlay1.add_controller(gesture_right);
    
    // The Context menu
    context_builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/context_menu.xml");
    auto gmenu = context_builder->get_object<Gio::MenuModel>("context_menu");
    context_menu.set_menu_model(gmenu);
    context_menu.set_parent(overlay1);
    context_menu.set_has_arrow(false);

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

    // Link signals
    btn_main.signal_clicked().connect(sigc::mem_fun(*this, &MenuWin::btnmain_clicked));
    btn_win1.signal_clicked().connect(sigc::mem_fun(*this, &MenuWin::btnwin1_clicked));
    btn_win2.signal_clicked().connect(sigc::mem_fun(*this, &MenuWin::btnwin2_clicked));
    window1.signal_close_request().connect(sigc::mem_fun(*this, &MenuWin::win1_closed),true);
    window2.signal_close_request().connect(sigc::mem_fun(*this, &MenuWin::win2_closed),true);

    window1.set_transient_for(*this);
    window2.set_transient_for(*this);

    // Add widgets to the window
    main_box.set_halign(Gtk::Align::FILL);
    main_box.set_valign(Gtk::Align::FILL);
    overlay1.add_overlay(main_box);
    set_child(overlay1);
}

void MenuWin::press(int n_press, double x, double y){
    // g_print("%f %f\n", x, y);
    Gdk::Rectangle point(x, y, 1, 1);
    context_menu.set_pointing_to(point);
    context_menu.popup();
}

// Return to main menu
void MenuWin::btnmain_clicked()
{
    window1.hide();
    window2.hide();
    menu_bar.change_menu(WinShown::DEFAULT);
}

// Launch Window1
void MenuWin::btnwin1_clicked()
{
    menu_bar.change_menu(WinShown::WIN_1);
    window1.show();
}

// Launch Window2
void MenuWin::btnwin2_clicked()
{
    menu_bar.change_menu(WinShown::WIN_2);
    window2.show();
}

// New a window
void MenuWin::new_win1()
{
    window1.show();
    menu_bar.change_menu(WinShown::WIN_1);
}

// Quit a window
void MenuWin::quit_win1()
{
    window1.hide();
    menu_bar.change_menu(WinShown::DEFAULT);
}

// 
bool MenuWin::win1_closed(){
    window1.hide();
    menu_bar.change_menu(WinShown::DEFAULT);
    return true;
}

// New a window
void MenuWin::new_win2()
{
    window2.show();
    menu_bar.change_menu(WinShown::WIN_2);
}

// Quit a window
void MenuWin::quit_win2()
{
    window2.hide();
    menu_bar.change_menu(WinShown::DEFAULT);
}

//
bool MenuWin::win2_closed(){
    window2.hide();
    menu_bar.change_menu(WinShown::DEFAULT);
    return true;
}

// Test to interact to the child class by global menu
void MenuWin::show_about_win1(){
    window1.about_win1();
}

void MenuWin::show_about_win2(){
    window2.about_win2();
}
