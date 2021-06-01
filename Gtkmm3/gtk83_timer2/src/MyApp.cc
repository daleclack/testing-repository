#include "MyApp.hh"

MyApp::MyApp()
:Gtk::Application("org.gtk.daleclack"),
timer_value(1000)
{
    Glib::set_application_name("Gtk83");
}

Glib::RefPtr<MyApp> MyApp::create(){
    return Glib::RefPtr<MyApp>(new MyApp());
}

void MyApp::on_activate()
{
    //Get builder and main window
    ref_builder=Gtk::Builder::create_from_file("../res/window.ui");
    ref_builder->get_widget("main_window",main_window);
    main_window->set_icon_name("org.gtk.daleclack");
    //Get widgets
    ref_builder->get_widget("clock_label",time_label);
    //Add actions
    add_action("start",sigc::mem_fun(*this,&MyApp::start_timer));
    add_action("pause",sigc::mem_fun(*this,&MyApp::disconnect_timer));
    add_action("empty",sigc::mem_fun(*this,&MyApp::empty_time));
    add_action("quit",sigc::mem_fun(*this,&MyApp::quit));
    //Show everything
    add_window(*main_window);
    main_window->show_all();
}

void MyApp::start_timer(){
    mytimer=Glib::signal_timeout().connect(sigc::mem_fun(*this,&MyApp::on_timeout),timer_value);
}

void MyApp::disconnect_timer(){
    mytimer.disconnect();
}

void MyApp::empty_time(){
    time_sum=0;
    time_label->set_label("0:00");
}

bool MyApp::on_timeout(){
    time_sum++;
    sprintf(time_string,"%d:%02d",time_sum/60,time_sum%60);
    time_label->set_label(time_string);
    return true;
}
