#include "MyApp.hh"

MyApp::MyApp()
:Gtk::Application("org.gtk.daleclack")
{
    Glib::set_application_name("Gtk82");
}

Glib::RefPtr<MyApp> MyApp::create(){
    return Glib::RefPtr<MyApp>(new MyApp());
}

void MyApp::on_startup(){
    Gtk::Application::on_startup();

}

void MyApp::on_activate(){
    Gtk::Window *main_window;
    ref_builder=Gtk::Builder::create_from_file("../res/window.ui");
    //Get widgets
    ref_builder->get_widget("main_window",main_window);
    ref_builder->get_widget("btn_1",btn1);
    ref_builder->get_widget("btn_2",btn2);
    ref_builder->get_widget("btn_3",btn3);
    ref_builder->get_widget("main_stack",main_stack);
    ref_builder->get_widget("btn_pg2",btnpg2);
    ref_builder->get_widget("frame1",frame1);
    ref_builder->get_widget("frame2",frame2);
    ref_builder->get_widget("frame3",frame3);
    //Default Page
    main_stack->set_visible_child(*frame1);
    //Click signal
    btn1->signal_clicked().connect(sigc::mem_fun(*this,&MyApp::btn1_clicked));
    btn2->signal_clicked().connect(sigc::mem_fun(*this,&MyApp::btn2_clicked));
    btn3->signal_clicked().connect(sigc::mem_fun(*this,&MyApp::btn3_clicked));
    btnpg2->signal_clicked().connect(sigc::mem_fun(*this,&MyApp::btnpg2_clicked));
    add_window(*main_window);
    main_window->show_all();
}

void MyApp::btn1_clicked(){
    
    main_stack->set_visible_child(*frame2);
}

void MyApp::btn2_clicked(){
    main_stack->set_visible_child(*frame1);
}

void MyApp::btn3_clicked(){
    main_stack->set_visible_child(*frame1);
}

void MyApp::btnpg2_clicked(){
    main_stack->set_visible_child(*frame3);
}
