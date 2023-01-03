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

    set_child(main_box);
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
