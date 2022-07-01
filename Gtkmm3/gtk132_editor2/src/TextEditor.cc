#include "TextEditor.hh"
#include "text_types.hh"
#include <fstream>

// Only for build in this repository
#define text_globs supported_globs

TextEditor::TextEditor()
:vbox(Gtk::ORIENTATION_VERTICAL,5),
hbox(Gtk::ORIENTATION_HORIZONTAL,5),
btnbox(Gtk::ORIENTATION_VERTICAL,5),
btn_copy("Copy"),
btn_paste("Paste"),
btn_open("Open"),
btn_save("Save"),
btn_clear("Clear")
{
    //Initalize Window
    set_default_size(800,450);
    set_icon_name("my_textedit");
    set_title("Simple Text Editor");
    
    //Initalize Text Buffers
    buffer1=textview1.get_buffer();
    buffer1->signal_changed().connect(sigc::mem_fun(*this,&TextEditor::buffer1_changed));

    //Pack Widgets
    sw1.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    sw1.add(textview1);
    btnbox.set_valign(Gtk::ALIGN_CENTER);
    btnbox.pack_start(btn_copy,Gtk::PACK_SHRINK);
    btnbox.pack_start(btn_paste,Gtk::PACK_SHRINK);
    btnbox.pack_start(btn_open,Gtk::PACK_SHRINK);
    btnbox.pack_start(btn_save,Gtk::PACK_SHRINK);
    btnbox.pack_start(btn_clear,Gtk::PACK_SHRINK);
    hbox.pack_start(sw1);
    hbox.pack_start(btnbox,Gtk::PACK_SHRINK);
    
    btn_open.signal_clicked().connect(sigc::mem_fun(*this,&TextEditor::btnopen_clicked));
    btn_save.signal_clicked().connect(sigc::mem_fun(*this,&TextEditor::btnsave_clicked));
    btn_copy.signal_clicked().connect(sigc::mem_fun(*this,&TextEditor::btncopy_clicked));
    btn_paste.signal_clicked().connect(sigc::mem_fun(*this,&TextEditor::btnpaste_clicked));
    btn_clear.signal_clicked().connect(sigc::mem_fun(*this,&TextEditor::btnclear_clicked));

    //A InfoBar
    infobar.add_button("OK",Gtk::RESPONSE_OK);
    infobar.signal_response().connect(sigc::mem_fun(*this,&TextEditor::infobar_response));
    infobox=dynamic_cast<Gtk::Box*>(infobar.get_content_area());
    infobox->pack_start(label1);
    vbox.pack_start(infobar,Gtk::PACK_SHRINK);

    //Disable Copy button
    btn_copy.set_sensitive(false);

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
    btn_copy.set_sensitive();
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
