#include "MyWin.hh"
#include <fstream>

MyWin::MyWin()
:btnsave("Save Config"),
btnload("Load Config from file"),
label1("Simple Text"),
main_box(Gtk::Orientation::VERTICAL,5)
{
    //Ininalize window
    set_icon_name("org.gtk.daleclack");
    set_default_size(400,300);
    set_title("Font Dialog");

    //Add Button
    Glib::ustring curr_font=fontbtn.get_font();
    Pango::FontDescription descript(curr_font);
    fontbtn.set_use_font();
    fontbtn.set_font(curr_font);
    fontbtn.signal_font_set().connect(sigc::mem_fun(*this,&MyWin::font_changed));
    btnsave.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::save_dialog));
    btnload.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::load_dialog));

    //Pack Widgets
    main_box.append(label1);
    main_box.append(fontbtn);
    main_box.append(btnload);
    main_box.append(btnsave);
    main_box.set_halign(Gtk::Align::CENTER);
    main_box.set_valign(Gtk::Align::CENTER);

    //Add everything
    set_child(main_box);
    //show_all_children();
}

void MyWin::load_dialog(){
    //Create the dialog
    dialog=Gtk::FileChooserNative::create("Select a Config File",*this,
                                          Gtk::FileChooser::Action::OPEN,"OK","Cancel");
    dialog->signal_response().connect(sigc::mem_fun(*this,&MyWin::load_font));

    //File Filters
    auto filter_conf=Gtk::FileFilter::create();
    filter_conf->set_name("Config File");
    filter_conf->add_pattern("*.conf");
    dialog->add_filter(filter_conf);

    auto filter_any=Gtk::FileFilter::create();
    filter_any->set_name("Any Files");
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);

    dialog->show();
}

void MyWin::load_font(int response){
    //Load the config from a file
    if(response==Gtk::ResponseType::ACCEPT){
        //Get Filename
        auto file=dialog->get_file();
        Glib::ustring filename=file->get_path();
        //Get The Fontname from a file
        char fontname[57];
        std::ifstream infile;
        infile.open(filename,std::ios_base::in);
        infile.getline(fontname,57);
        fontbtn.set_font(fontname);
        infile.close();
        //Change the font
        font_changed();
        //Free Memory
        file.reset();
    }
    dialog.reset();
}

void MyWin::save_dialog(){
    //Create the dialog
    dialog=Gtk::FileChooserNative::create("Select a file to save",*this,
                                          Gtk::FileChooser::Action::SAVE,"OK","Cancel");
    dialog->signal_response().connect(sigc::mem_fun(*this,&MyWin::save_font));

    //File Filters
    auto filter_conf=Gtk::FileFilter::create();
    filter_conf->set_name("Config File");
    filter_conf->add_pattern("*.conf");
    dialog->add_filter(filter_conf);

    auto filter_any=Gtk::FileFilter::create();
    filter_any->set_name("Any Files");
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);

    dialog->show();
}

void MyWin::save_font(int response){
    //Save Font Config to a file
    if(response==Gtk::ResponseType::ACCEPT){
        //Get Filename
        auto file=dialog->get_file();
        Glib::ustring filename=file->get_path();
        //Save File
        std::ofstream outfile;
        outfile.open(filename,std::ios_base::out);
        outfile<<fontbtn.get_font();
        outfile.close();
        file.reset();
    }
    dialog.reset();
}

void MyWin::font_changed(){
    //Set Font Description
    Pango::FontDescription descript(fontbtn.get_font());
    auto font=Pango::AttrFontDesc::create_attr_font_desc(descript);
    
    //Append to list
    Pango::AttrList list;
    list.insert(font);
    label1.set_attributes(list);
}
