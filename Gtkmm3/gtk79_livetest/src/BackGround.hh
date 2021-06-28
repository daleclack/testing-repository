#pragma once

#include <gtkmm.h>

class BackGround : public Gtk::Dialog
{
public:
    BackGround(Gtk::Window &parent,Gtk::Image *back);
    void default_background();
protected:
    void on_response(int response_id) override;
private:
    //Child widgets
    Gtk::Button btn_default;
    Gtk::Button btn_set;
    Gtk::Image * background;
    //Signal Handlers
    void btnset_clicked();
};