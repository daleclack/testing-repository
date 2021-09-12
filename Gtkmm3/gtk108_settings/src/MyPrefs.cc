#include "MyPrefs.hh"
#include "image_types.hh"

MyPrefs::MyPrefs(BaseObjectType* cobject,const Glib::RefPtr<Gtk::Builder>& builder)
:Gtk::Dialog(cobject),
m_builder(builder)
{
    //Get Widgets
    m_builder->get_widget("width_spin",m_width);
    m_builder->get_widget("height_spin",m_height);
    m_builder->get_widget("back_entry",back_entry);
    m_builder->get_widget("btnopen",btnopen);
    m_builder->get_widget("btnget",btnget);
    m_builder->get_widget("btndefback",btndefback);
    m_builder->get_widget("btndefsize",btndefsize);

    //Initalize Dialog
    set_icon_name("org.gtk.daleclack");
    set_title("Preferences");

    //Create Settings
    m_settings=Gio::Settings::create("org.gtk.daleclack");
    m_settings->bind("width",m_width->property_value());
    m_settings->bind("height",m_height->property_value());
    m_settings->bind("background",back_entry->property_text());

    //Link Signals
    btnopen->signal_clicked().connect(sigc::mem_fun(*this,&MyPrefs::btnopen_clicked));
    btnget->signal_clicked().connect(sigc::mem_fun(*this,&MyPrefs::btnget_clicked));
    btndefsize->signal_clicked().connect(sigc::mem_fun(*this,&MyPrefs::btndefsize_clicked));
    btndefback->signal_clicked().connect(sigc::mem_fun(*this,&MyPrefs::btndefback_clicked));
}

void MyPrefs::btnopen_clicked(){
    //Initalize dialog
    auto parent=get_transient_for();
    dialog=Gtk::FileChooserNative::create("Open a Image File",*parent,Gtk::FILE_CHOOSER_ACTION_OPEN,
                                          "OK","Cancel");
    dialog->set_modal();
    dialog->signal_response().connect(sigc::mem_fun(*this,&MyPrefs::dialog_response));

    //Add Filters
    auto filter_image=Gtk::FileFilter::create();
    filter_image->set_name("Image Files");
    if(mime_type_supported()){
        filter_image->add_mime_type("image/*");
    }else{
        for(int i=0;supported_globs!=NULL && supported_globs[i]!=NULL;i++){
            const char * glob=supported_globs[i];
            filter_image->add_pattern(glob);
        }
    }
    dialog->add_filter(filter_image);

    auto filter_any=Gtk::FileFilter::create();
    filter_any->set_name("Any Files");
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);

    dialog->show();
}

void MyPrefs::btnget_clicked(){     //Get Current window size
    int width,height;
    auto win=get_transient_for();
    win->get_size(width,height);
    m_width->set_value(width);
    m_height->set_value(height);
}

void MyPrefs::btndefsize_clicked(){     //Default Size:640x360 
    m_width->set_value(640.0);
    m_height->set_value(360.0);
}

void MyPrefs::btndefback_clicked(){     //"none":Use Default Background
    back_entry->set_text("none");
}

void MyPrefs::dialog_response(int response_id){         //Get FileName
    if(response_id == Gtk::RESPONSE_ACCEPT){
        auto file=dialog->get_file();
        auto filename=file->get_path();
        back_entry->set_text(filename);
        file.reset();
    }
    dialog.reset();
}

MyPrefs * MyPrefs::create(Gtk::Window& parent){
    //Load the builder file and create dialog
    auto ref_builder=Gtk::Builder::create_from_resource("/gtk108/prefs.ui");

    MyPrefs* dialog=nullptr;
    ref_builder->get_widget_derived("prefs",dialog);
    dialog->set_transient_for(parent);

    return dialog;
}
