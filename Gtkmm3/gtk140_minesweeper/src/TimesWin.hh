#pragma once

#include <gtkmm.h>
#include <string>
#include "jsonfile.hh"

class TimesWin : public Gtk::Dialog
{
public:
    TimesWin();
    void insert_data(int time, std::string& name);
    times_map data;

protected:
    void on_response(int response_id) override;
};
