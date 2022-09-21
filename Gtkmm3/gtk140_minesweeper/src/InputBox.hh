#pragma once

#include <gtkmm.h>

class InputBox : public Gtk::Dialog
{
public:
    InputBox();

protected:
    void on_response(int response_id);

private:
    Gtk::Entry entry_name;
};