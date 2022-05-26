#pragma once

#include <gtkmm.h>

class MyWin : public Gtk::Window
{
public:
    static MyWin *create();
    MyWin(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade);

private:
    // Main GtkBuilder
    Glib::RefPtr<Gtk::Builder> ref_builder;

    // Calculator Class
    int pos;
    bool focused, winned;
    Glib::ustring tmp;

    // Child widgets
    Gtk::Entry *entry_ans;
    Gtk::Button *btns[16], *btnstart, *btnnext, *btncheck, *btnclear, *btnexit;

    // Signal Handlers
    void btns_clicked(Gtk::Button *button);
    void btnstart_clicked();
    void btnnext_clicked();
    void btncheck_clicked();
    void btnclear_clicked();
    void entry_ans_focus();
};