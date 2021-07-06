#include "MyWin.hh"
#include <fstream>

MyWin::MyWin()
:btnsave("Save Config"),
btnload("Load Config from file"),
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
    btnsave.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::save_dialog));
    btnload.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::load_dialog));

    //Pack Buttons
    main_box.pack_start(label1,Gtk::PACK_SHRINK);
    main_box.pack_start(fontbtn,Gtk::PACK_SHRINK);
    main_box.pack_start(btnload,Gtk::PACK_SHRINK);
    main_box.pack_start(btnsave,Gtk::PACK_SHRINK);
    main_box.set_halign(Gtk::ALIGN_CENTER);
    main_box.set_valign(Gtk::ALIGN_CENTER);

    //Add everything
    add(main_box);
    show_all_children();
}

void MyWin::load_dialog(){
    //Create the dialog
    dialog=Gtk::FileChooserNative::create("Select a Config File",*this,
                                          Gtk::FILE_CHOOSER_ACTION_OPEN,"OK","Cancel");
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
    if(response==Gtk::RESPONSE_ACCEPT){
        Glib::ustring filename=dialog->get_filename();
        char fontname[57];
        std::ifstream infile;
        infile.open(filename,std::ios_base::in);
        infile.getline(fontname,57);
        fontbtn.set_font_name(fontname);
        infile.close();
        font_changed();
    }
    dialog.reset();
}

void MyWin::save_dialog(){
    //Create the dialog
    dialog=Gtk::FileChooserNative::create("Select a file to save",*this,
                                          Gtk::FILE_CHOOSER_ACTION_SAVE,"OK","Cancel");
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
    if(response==Gtk::RESPONSE_ACCEPT){
        Glib::ustring filename=dialog->get_filename();
        std::ofstream outfile;
        outfile.open(filename,std::ios_base::out);
        outfile<<fontbtn.get_font_name();
        outfile.close();
    }
    dialog.reset();
}

void MyWin::font_changed(){
    //Set a font for the label
    Pango::FontDescription descript(fontbtn.get_font_name());
    fontbtn.set_label(fontbtn.get_font_name());
    label1.override_font(descript);
}
