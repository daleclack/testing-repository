#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window
{
public:
    MyWin(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade);
    static MyWin *create();

private:
    // Child widgets
    Gtk::Stack *main_stack;
    Gtk::Overlay *main_overlay;
    Gtk::Grid *start_page, *launchpad_page;
    Gtk::Image *background;
    Gtk::Button *btnstart, *btnback;

    // Style Config
    Glib::RefPtr<Gtk::CssProvider> provider;

    // Builder for widgets
    Glib::RefPtr<Gtk::Builder> ref_builder;
    void btnstart_clicked();
    void btnback_clicked();
};
