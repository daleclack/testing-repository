#pragma once

#include <gtkmm.h>

class MyApp : public Gtk::Application{
protected:
    MyApp();
public:
    static Glib::RefPtr<MyApp> create();
protected:
    void on_activate() override;
private:
    //Main Builder
    Glib::RefPtr<Gtk::Builder> ref_builder;
    Gtk::Window *main_window;

    //The Timer
    sigc::connection mytimer;
    const int timer_value;
    bool on_timeout();
    int time_sum=0;
    char time_string[20];

    //Child Widgets
    Gtk::Label *time_label;
    
    //Signal Handlers
    void start_timer();
    void disconnect_timer();
    void empty_time();
};