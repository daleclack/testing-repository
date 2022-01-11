#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window
{
public:
    static MyWin *create();
    MyWin(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);

private:
    Glib::RefPtr<Gtk::Builder> ref_builder;

    // Child Widgets
    Gtk::Button *btn_go, *btn_back;
    Gtk::Grid *start_grid, *test_grid;
    Gtk::Stack *main_stack;

    //Signal Handlers
    void btngo_clicked();
    void btnback_clicked();

};
