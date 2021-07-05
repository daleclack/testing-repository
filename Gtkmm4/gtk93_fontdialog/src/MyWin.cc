#include "MyWin.hh"
#include <iostream>

MyWin::MyWin()
:fontbtn("Sans 10"),
label1("Simple Text"),
main_box(Gtk::Orientation::VERTICAL,5)
{
    //Ininalize window
    set_icon_name("org.gtk.daleclack");
    set_default_size(400,300);
    set_title("Font Dialog");

    //Add Button
    fontbtn.set_use_font();
    fontbtn.signal_font_set().connect(sigc::mem_fun(*this,&MyWin::font_changed));
    main_box.append(label1);
    main_box.append(fontbtn);
    main_box.set_halign(Gtk::Align::CENTER);
    main_box.set_valign(Gtk::Align::CENTER);

    //Add everything
    set_child(main_box);
    //show_all_children();
}

void MyWin::font_changed(){
    Pango::FontDescription descript(fontbtn.get_font());
    auto font=Pango::AttrFontDesc::create_attr_font_desc(descript);
    Pango::AttrList list;
    list.insert(font);
    label1.set_attributes(list);
}
