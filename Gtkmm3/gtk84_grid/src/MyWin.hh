#pragma once

#include <gtkmm.h>
#include "MyBtn.hh"

class MyWin : public Gtk::Window{
public:
    MyWin();
    virtual ~MyWin();
private:
    //Child widgets
    Gtk::Window window1;
    Gtk::ScrolledWindow sw;
    Gtk::Grid *grid1;
    Gtk::Box vbox,entrybox1,entrybox2;
    Gtk::Label row_label,col_label;
    Gtk::Entry row_entry,col_entry;
    Gtk::Button btn_ok;
    MyBtn *pBtn,*pBtn1;
    //Signal Handlers
    void btnok_clicked();
    void pbtn_clicked(MyBtn *pBtn1);
};