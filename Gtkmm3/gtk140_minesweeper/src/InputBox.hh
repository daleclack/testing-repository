#pragma once

#include <gtkmm.h>
#include "jsonfile.hh"

class InputBox : public Gtk::Dialog
{
public:
    InputBox();
    void read_json_file();
    times_map scores_map;

protected:
    void on_response(int response_id);

private:
    Gtk::Entry entry_name;
    Gtk::Label main_label;
};
