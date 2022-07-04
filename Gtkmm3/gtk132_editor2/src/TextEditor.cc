#include "TextEditor.hh"
#include "text_types.hh"
#include <fstream>

// Only for build in this repository
#define text_globs supported_globs

TextEditor::TextEditor()
:vbox(Gtk::ORIENTATION_VERTICAL,5),
hbox(Gtk::ORIENTATION_HORIZONTAL,5)
{
    //Initalize Window
    set_default_size(800,450);
    set_icon_name("my_textedit");

    //Initalize HeaderBar
    header.set_decoration_layout("close,minimize,maximize:menu");
    header.set_show_close_button();
    menubtn.set_image_from_icon_name("open-menu");
    header.pack_end(menubtn);
    header.set_title("Simple Text Editor");
    set_titlebar(header);

    //Add a menu
    menu_builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/text_menu.xml");
    auto object = menu_builder->get_object("text_menu");
    auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
    popover.bind_model(gmenu);
    menubtn.set_popover(popover);
    
    //Initalize Text Buffers
    buffer1=textview1.get_buffer();
    buffer1->signal_changed().connect(sigc::mem_fun(*this,&TextEditor::buffer1_changed));

    //Pack Widgets
    sw1.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    sw1.add(textview1);
    hbox.pack_start(sw1);
    
    //Add actions and signal handlers
    add_action("text_open",sigc::mem_fun(*this,&TextEditor::btnopen_clicked));
    add_action("text_save",sigc::mem_fun(*this,&TextEditor::btnsave_clicked));
    add_action("text_copy",sigc::mem_fun(*this,&TextEditor::btncopy_clicked));
    add_action("text_paste",sigc::mem_fun(*this,&TextEditor::btnpaste_clicked));
    add_action("text_clear",sigc::mem_fun(*this,&TextEditor::btnclear_clicked));

    //A InfoBar
    infobar.add_button("OK",Gtk::RESPONSE_OK);
    infobar.signal_response().connect(sigc::mem_fun(*this,&TextEditor::infobar_response));
    infobox=dynamic_cast<Gtk::Box*>(infobar.get_content_area());
    infobox->pack_start(label1);
    vbox.pack_start(infobar,Gtk::PACK_SHRINK);

    //Show everything
    vbox.pack_start(hbox);
    add(vbox);
    show_all_children();
    infobar.hide();
}

void TextEditor::btnopen_clicked(){
    //Create a dialog
    dialog=Gtk::FileChooserNative::create("Open a text file",*this,
        Gtk::FILE_CHOOSER_ACTION_OPEN,"OK","Cancel");
    
    dialog->signal_response().connect(sigc::mem_fun(*this,&TextEditor::opendialog_response));

    //Add Filters
    auto filter=Gtk::FileFilter::create();
    filter->set_name("Text Files");
    if(mimetype_supported()){
        filter->add_mime_type("text/*");
    }else{
        for(int i = 0; text_globs != NULL && text_globs[i] != NULL; i++){
            const char *glob = text_globs[i];
            filter->add_pattern(glob);
        }
    }
    dialog->add_filter(filter);

    auto filter_any=Gtk::FileFilter::create();
    filter_any->set_name("Any Files");
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);

    dialog->show();
}

void TextEditor::opendialog_response(int response){
    if(response==Gtk::RESPONSE_ACCEPT){
        //Load Contents of a file
        auto file=dialog->get_file();
        char * contents;
        gsize length;
        if(file->load_contents(contents,length)){
            buffer1->set_text(contents);
        }
    }
    dialog.reset();
}

void TextEditor::btnsave_clicked(){
    //Create a dialog
    dialog=Gtk::FileChooserNative::create("Save file",*this,
        Gtk::FILE_CHOOSER_ACTION_SAVE,"OK","Cancel");
    
    dialog->signal_response().connect(sigc::mem_fun(*this,&TextEditor::savedialog_response));

    //Add Filters
    auto filter=Gtk::FileFilter::create();
    filter->set_name("Text Files");
    if(mimetype_supported()){
        filter->add_mime_type("text/*");
    }else{
        for(int i = 0; text_globs != NULL && text_globs[i] != NULL; i++){
            const char *glob = text_globs[i];
            filter->add_pattern(glob);
        }
    }
    dialog->add_filter(filter);

    auto filter_any=Gtk::FileFilter::create();
    filter_any->set_name("Any Files");
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);

    dialog->show();
}

void TextEditor::savedialog_response(int response){
    if(response==Gtk::RESPONSE_ACCEPT){
        //Get Filename
        auto file=dialog->get_file();
        std::string filename=file->get_path();
        //Get Text
        Glib::ustring text;
        text=buffer1->get_text();
        //Save to a file
        std::ofstream outfile;
        outfile.open(filename,std::ios_base::out);
        outfile<<text;
        outfile.close();
    }
    dialog.reset();
}

void TextEditor::buffer1_changed(){
    //When the text changed,enable the copy button
    
}

void TextEditor::btncopy_clicked(){
    //Get Text
    Glib::ustring text;
    Gtk::TextBuffer::iterator start,end;
    if(buffer1->get_selection_bounds(start,end)){
        text=buffer1->get_text(start,end);
    }else{
        text=buffer1->get_text();
    }

    //Get Clipboard and set text
    auto refClipboard=Gtk::Clipboard::get();
    refClipboard->set_text(text);

    //Show InfoBar
    label1.set_label("The Text is copyed");
    infobar.show();
}

void TextEditor::btnpaste_clicked(){
    //Get ClipBoard
    auto refClipboard=Gtk::Clipboard::get();
    refClipboard->request_text(sigc::mem_fun(*this,&TextEditor::clipboard_receive));
}

void TextEditor::clipboard_receive(const Glib::ustring &text){
    if(buffer1->insert_interactive_at_cursor(text)){
        //Show InfoBar
        label1.set_label("The Text is Pasted at cursor position");
        infobar.show();
    }else{
        //Show InfoBar
        label1.set_label("Text Paste Error!");
        infobar.show();
    }
}

void TextEditor::btnclear_clicked(){
    buffer1->set_text("");
}

void TextEditor::infobar_response(int response){
    infobar.hide();
}
