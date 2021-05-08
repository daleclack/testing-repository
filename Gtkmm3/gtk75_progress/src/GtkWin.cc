#include "GtkWin.hh"

GtkWin::GtkWin()
:hbox(Gtk::ORIENTATION_VERTICAL,5),
checkshow("Show text"),
check_activity("Activity Mode"),
check_inverted("Right to Left"),
btn_exit("Exit")
{
    set_icon_name("org.gtk.daleclack");
    set_title("Gtk (75)");
    set_default_size(300,300);
    set_border_width(10);
    //Initalize Progress Bar
    progress1.set_text("Progress Test");
    progress1.set_show_text();
    hbox.pack_start(progress1);
    //Add a timer
    connection_timeout=Glib::signal_timeout().connect(sigc::mem_fun(*this,&GtkWin::on_timeout),50);
    //Check Button
    checkshow.signal_clicked().connect(sigc::mem_fun(*this,&GtkWin::checkshow_clicked));
    checkshow.set_active();
    hbox.pack_start(checkshow);
    //Activity mode
    check_activity.signal_clicked().connect(sigc::mem_fun(*this,&GtkWin::activity_clicked));
    hbox.pack_start(check_activity);
    //Inverted Mode
    check_inverted.signal_clicked().connect(sigc::mem_fun(*this,&GtkWin::invert_clicked));
    hbox.pack_start(check_inverted);
    //"Exit" button
    btn_exit.signal_clicked().connect(sigc::mem_fun(*this,&GtkWin::exit_clicked));
    hbox.pack_end(btn_exit);
    add(hbox);
    show_all();
}

void GtkWin::checkshow_clicked(){
    bool checked=checkshow.get_active();
    progress1.set_show_text(checked);
}

void GtkWin::activity_clicked(){
    activity_mode=check_activity.get_active();
    if(activity_mode){
        progress1.pulse();
    }else{
        progress1.set_fraction(0.0);
    }
}

void GtkWin::invert_clicked(){
    bool inverted=check_inverted.get_active();
    progress1.set_inverted(inverted);
}

bool GtkWin::on_timeout(){
    //Change the progress Bar Value
    if(activity_mode){
        progress1.pulse();
    }else{
        double new_val=progress1.get_fraction()+0.01;
        if(new_val>1.0){
            new_val=0.0;
        }
        progress1.set_fraction(new_val);
    }
    return true;
}

void GtkWin::exit_clicked(){
    hide();
}

GtkWin::~GtkWin(){
}