#include "MyWin.hh"

MyWin::MyWin()
:main_box(Gtk::ORIENTATION_VERTICAL,5),
btnbox(Gtk::ORIENTATION_VERTICAL,5)
{
    //Add Widgets
    set_default_size(800,450);
    set_icon_name("org.gtk.daleclack");
    
    //Scrolled Window
    sw.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    sw.add(image_area);
    main_box.pack_start(sw);

    main_box.pack_start(btnbox,Gtk::PACK_SHRINK);

    add(main_box);
    show_all_children();
}