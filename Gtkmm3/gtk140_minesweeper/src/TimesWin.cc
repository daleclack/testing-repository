#include "TimesWin.hh"

TimesWin::TimesWin()
{
}

void TimesWin::insert_data(int time, std::string& name){
    // Insert data to map
    data[name] = std::to_string(time);
}

void TimesWin::on_response(int response_id)
{
}