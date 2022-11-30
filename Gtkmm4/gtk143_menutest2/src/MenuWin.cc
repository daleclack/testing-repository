#include "MenuWin.hh"
#include "Win1.hh"
#include "Win2.hh"

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
    set_default_size(300, 200);

    // Create models
    builder_def = Gtk::Builder::create_from_resource("/org/gtk/daleclack/default_menu.xml");
    model_default = builder_def->get_object<Gio::MenuModel>("default_menu");
    builder_win1 = Gtk::Builder::create_from_resource("/org/gtk/daleclack/win1_menu.xml");
    model_win1 = builder_win1->get_object<Gio::MenuModel>("win1_menu");
    builder_win2 = Gtk::Builder::create_from_resource("/org/gtk/daleclack/win2_menu.xml");
    model_win2 = builder_win2->get_object<Gio::MenuModel>("win2_menu");

    // Add actions
    add_action("new_win1", sigc::mem_fun(*this, &MenuWin::new_win1));
    add_action("quit_win1", sigc::mem_fun(*this, &MenuWin::quit_win1));
    add_action("new_win2", sigc::mem_fun(*this, &MenuWin::new_win2));
    add_action("quit_win2", sigc::mem_fun(*this, &MenuWin::quit_win2));

    // Add popover menu bar
    menu_bar = new Gtk::PopoverMenuBar(model_default);
    main_box.append(*menu_bar);

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

    window1.set_transient_for(*this);
    window2.set_transient_for(*this);

    set_child(main_box);
}

// Return to main menu
void MenuWin::btnmain_clicked()
{
    window1.hide();
    window2.hide();
    menu_bar->set_menu_model(model_default);
}

// Launch Window1
void MenuWin::btnwin1_clicked()
{
    menu_bar->set_menu_model(model_win1);
    window1.show();
}

// Launch Window2
void MenuWin::btnwin2_clicked()
{
    menu_bar->set_menu_model(model_win2);
    window2.show();
}

// New a window
void MenuWin::new_win1()
{
    window1.show();
    menu_bar->set_menu_model(model_win1);
}

// Quit a window
void MenuWin::quit_win1()
{
    window1.hide();
    menu_bar->set_menu_model(model_default);
}

// New a window
void MenuWin::new_win2()
{
    window2.show();
    menu_bar->set_menu_model(model_win2);
}

// Quit a window
void MenuWin::quit_win2()
{
    window2.hide();
    menu_bar->set_menu_model(model_default);
}

MenuWin::~MenuWin()
{
    delete menu_bar;
}