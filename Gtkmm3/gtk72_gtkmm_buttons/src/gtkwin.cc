#include <cstdio>
#include "gtkwin.hh"

GtkWin::GtkWin()
:button1("Write Config"),
check1("Check 1"),
hbox(Gtk::ORIENTATION_VERTICAL)
{
    //Initalize Window
    set_icon_name("org.gtk.daleclack");
    set_default_size(200,250);
    add(hbox);
    //Initalize check status
    rb[1].set_active();
    rb[0].set_label("Selection 1");
    rb[1].set_label("Selection 2");
    rb[1].join_group(rb[0]);
    rb[2].set_label("Selection 3");
    rb[2].join_group(rb[0]);
    //Initalize box and buttons
    hbox.pack_start(check1);
    hbox.pack_start(separtor);
    hbox.pack_start(rb[0]);
    hbox.pack_start(rb[1]);
    hbox.pack_start(rb[2]);
    hbox.pack_start(separtor1);
    hbox.pack_start(button1);
    button1.signal_clicked().connect(sigc::mem_fun(*this,&GtkWin::write_config));
    //top_box.pack_start(hbox);
    //Set Button Status and show all widgets
    get_config();
    show_all();
}

GtkWin::~GtkWin(){
}

void GtkWin::get_config(){
    //Get Config from a file and set active
    int check_active=1,radio_index=1;
    freopen("config","r",stdin);
    scanf("checkbutton=%d",&check_active);
    getchar();
    scanf("radiobutton=%d",&radio_index);
    fclose(stdin);
    check1.set_active(check_active);
    rb[radio_index].set_active();
}

void GtkWin::write_config(){
    //Write Config to a config file
    freopen("config","w",stdout);
    printf("checkbutton=%d\n",check1.get_active());
    for(int i=0;i<3;i++){
        if(rb[i].get_active()==true){
            printf("radiobutton=%d",i);
        }
    }
    fclose(stdout);
}