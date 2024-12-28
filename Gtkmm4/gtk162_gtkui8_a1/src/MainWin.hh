#pragma once

#include <gtkmm.h>

class MainWin : public Gtk::ApplicationWindow
{
public:
    MainWin();
    virtual ~MainWin();
protected:
    //Signal handlers:
    // void on_button_clicked();
private:
    // Gtk::Button m_button;
};
