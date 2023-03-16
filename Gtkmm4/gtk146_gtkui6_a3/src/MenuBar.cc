#include "MenuBar.hh"

MenuBar::MenuBar()
{
    // Create models
    builder_def = Gtk::Builder::create_from_resource("/org/gtk/daleclack/default_menu.xml");
    model_default = builder_def->get_object<Gio::MenuModel>("default_menu");
    menubar = Gtk::make_managed<Gtk::PopoverMenuBar>(model_default);
}

void MenuBar::change_menu(WinShown win_id)
{
    // Switch the menu for a window
    switch (win_id)
    {
    case WinShown::DEFAULT:
        menubar->set_menu_model(model_default);
        break;
    case WinShown::WIN_1:
        // menubar->set_menu_model(model_win1);
        break;
    case WinShown::WIN_2:
        // menubar->set_menu_model(model_win2);
        break;
    }
}

MenuBar::~MenuBar(){
}
