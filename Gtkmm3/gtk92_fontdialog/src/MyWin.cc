#include "MyWin.hh"
#include <iostream>

MyWin::MyWin()
:
label1("Simple Text"),
main_box(Gtk::ORIENTATION_VERTICAL,5)
{
    //Ininalize window
    set_icon_name("org.gtk.daleclack");
    set_default_size(400,300);
    set_title("Font Dialog");

    //Add Button
    Glib::ustring curr_font=fontbtn.get_font_name();
    Pango::FontDescription descript(curr_font);
    fontbtn.set_label(curr_font);
    fontbtn.set_use_font();
    fontbtn.signal_font_set().connect(sigc::mem_fun(*this,&MyWin::font_changed));
    label1.override_font(descript);
    main_box.pack_start(label1,Gtk::PACK_SHRINK);
    main_box.pack_start(fontbtn,Gtk::PACK_SHRINK);
    main_box.set_halign(Gtk::ALIGN_CENTER);
    main_box.set_valign(Gtk::ALIGN_CENTER);

    //Add everything
    add(main_box);
    show_all_children();
}

void MyWin::font_changed(){
    Pango::FontDescription descript(fontbtn.get_font_name());
    fontbtn.set_label(fontbtn.get_font_name());
    label1.override_font(descript);
}
