#include "MyWin.hh"
#include "winpe.xpm"

MyWin::MyWin()
:btn_back("Change Background")
{
    set_icon_name("org.gtk.daleclack");
    set_default_size(640,360);
    //Add Overlay and image to the window
    add(overlay);
    overlay.add(back);
    //Add the button
    btn_back.set_halign(Gtk::ALIGN_CENTER);
    btn_back.set_valign(Gtk::ALIGN_CENTER);
    btn_back.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnback_clicked));
    overlay.add_overlay(btn_back);
    //Background
    Glib::RefPtr<Gdk::Pixbuf> pixbuf=Gdk::Pixbuf::create_from_xpm_data(winpe);
    Glib::RefPtr<Gdk::Pixbuf> sized=pixbuf->scale_simple(640,360,Gdk::INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(back.gobj(),sized->gobj());
    //Release Memory
    pixbuf.reset();
    sized.reset();
    //Show all children
    show_all_children();
}

void MyWin::btnback_clicked(){
    Gtk::FileChooserDialog dialog1("Choose an image file",
                                  Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog1.set_transient_for(*this);

    //Add reponse buttons
    dialog1.add_button("_Cancel",Gtk::RESPONSE_CANCEL);
    dialog1.add_button("_OK",Gtk::RESPONSE_OK);
    
    //Add filters
    auto filter_image=Gtk::FileFilter::create();
    filter_image->set_name("Image Files");
    filter_image->add_mime_type("image/*");
    dialog1.add_filter(filter_image);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog1.add_filter(filter_any);

    //Show the dialog and wait for a user response:
    int result = dialog1.run();

    if(result==Gtk::RESPONSE_OK){
        //Get the image file and set the image from the file
        std::string filename;
        filename=dialog1.get_filename();
        Glib::RefPtr<Gdk::Pixbuf> pixbuf=Gdk::Pixbuf::create_from_file(filename);
        Glib::RefPtr<Gdk::Pixbuf> sized=pixbuf->scale_simple(640,360,Gdk::INTERP_BILINEAR);
        gtk_image_set_from_pixbuf(back.gobj(),sized->gobj());
        //Free the memory
        pixbuf.reset();
        sized.reset();
    }
    filter_image.reset();
    filter_any.reset();
}

MyWin::~MyWin(){
}
