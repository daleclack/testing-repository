#include "TextEditor.hh"
#include "text_types.hh"
#include <fstream>
#include <iostream>

// Only for build in this repository
#define text_globs supported_globs

TextEditor::TextEditor()
    : vbox(Gtk::ORIENTATION_VERTICAL, 5),
      hbox(Gtk::ORIENTATION_HORIZONTAL, 5),
      searchbox(Gtk::ORIENTATION_HORIZONTAL, 5),
      file_opened(false)
{
    // Initalize Window
    set_default_size(800, 450);
    set_icon_name("my_textedit");

    // Initalize HeaderBar
    header.set_decoration_layout("close,minimize,maximize:menu");
    header.set_show_close_button();
    menubtn.set_image_from_icon_name("open-menu");
    search_button.set_image_from_icon_name("find");
    header.pack_end(menubtn);
    header.pack_end(search_button);
    header.set_title("Simple Text Editor");
    set_titlebar(header);

    // Add a menu
    menu_builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/text_menu.xml");
    auto object = menu_builder->get_object("text_menu");
    auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
    popover.bind_model(gmenu);
    menubtn.set_popover(popover);

    // Initalize Text Buffers
    buffer1 = textview1.get_buffer();
    buffer1->signal_changed().connect(sigc::mem_fun(*this, &TextEditor::buffer1_changed));

    // Pack Widgets
    sw1.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    sw1.add(textview1);
    hbox.pack_start(sw1);

    // Add actions and signal handlers
    add_action("text_open", sigc::mem_fun(*this, &TextEditor::btnopen_clicked));
    add_action("text_save", sigc::mem_fun(*this, &TextEditor::btnsave_clicked));
    add_action("text_saveas", sigc::mem_fun(*this, &TextEditor::btnsaveas_clicked));
    add_action("text_copy", sigc::mem_fun(*this, &TextEditor::btncopy_clicked));
    add_action("text_paste", sigc::mem_fun(*this, &TextEditor::btnpaste_clicked));
    add_action("text_close", sigc::mem_fun(*this, &TextEditor::btnclose_clicked));
    add_action("text_about", sigc::mem_fun(*this, &TextEditor::about_activated));

    // Add searchbar and search up and down buttons
    search_up.set_image_from_icon_name("up");
    search_down.set_image_from_icon_name("down");

    // Bind property and signals
    search_binding = Glib::Binding::bind_property(search_button.property_active(),
                                                  searchbar.property_search_mode_enabled(),
                                                  Glib::BINDING_BIDIRECTIONAL);
    search_entry.signal_changed().connect(sigc::mem_fun(*this, &TextEditor::search_entry_changed));
    search_up.signal_clicked().connect(sigc::mem_fun(*this, &TextEditor::search_backward));
    search_down.signal_clicked().connect(sigc::mem_fun(*this, &TextEditor::search_forward));

    // Pack widgets
    searchbox.pack_start(search_entry, Gtk::PACK_SHRINK);
    searchbox.pack_start(search_up, Gtk::PACK_SHRINK);
    searchbox.pack_start(search_down, Gtk::PACK_SHRINK);
    searchbar.add(searchbox);
    vbox.pack_start(searchbar, Gtk::PACK_SHRINK);

    // A InfoBar
    infobar.add_button("OK", Gtk::RESPONSE_OK);
    infobar.signal_response().connect(sigc::mem_fun(*this, &TextEditor::infobar_response));
    infobox = dynamic_cast<Gtk::Box *>(infobar.get_content_area());
    infobox->pack_start(label1);
    vbox.pack_start(infobar, Gtk::PACK_SHRINK);

    // Show everything
    vbox.pack_start(hbox);
    add(vbox);
    show_all_children();
    infobar.hide();
}

void TextEditor::btnopen_clicked()
{
    // Create a dialog
    dialog = Gtk::FileChooserNative::create("Open a text file", *this,
                                            Gtk::FILE_CHOOSER_ACTION_OPEN, "OK", "Cancel");

    dialog->signal_response().connect(sigc::mem_fun(*this, &TextEditor::opendialog_response));

    // Add Filters
    auto filter = Gtk::FileFilter::create();
    filter->set_name("Text Files");
    if (mimetype_supported())
    {
        filter->add_mime_type("text/*");
    }
    else
    {
        for (int i = 0; text_globs != NULL && text_globs[i] != NULL; i++)
        {
            const char *glob = text_globs[i];
            filter->add_pattern(glob);
        }
    }
    dialog->add_filter(filter);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any Files");
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);

    dialog->show();
}

void TextEditor::opendialog_response(int response)
{
    if (response == Gtk::RESPONSE_ACCEPT)
    {
        // Load Contents of a file
        auto file = dialog->get_file();
        curr_filename = file->get_path();
        file_opened = true;
        char *contents;
        gsize length;
        if (file->load_contents(contents, length))
        {
            buffer1->set_text(contents);
        }
    }
    dialog.reset();
}

void TextEditor::btnsave_clicked()
{
    if (file_opened)
    {
        // Get Text
        Glib::ustring text;
        text = buffer1->get_text();
        // Set file opened to true to use save mode
        file_opened = true;
        // Save to a file
        std::ofstream outfile;
        outfile.open(curr_filename, std::ios_base::out);
        outfile << text;
        outfile.close();
    }
}

void TextEditor::btnsaveas_clicked()
{
    // Create a dialog
    dialog = Gtk::FileChooserNative::create("Save file", *this,
                                            Gtk::FILE_CHOOSER_ACTION_SAVE, "OK", "Cancel");

    dialog->signal_response().connect(sigc::mem_fun(*this, &TextEditor::savedialog_response));

    // Add Filters
    auto filter = Gtk::FileFilter::create();
    filter->set_name("Text Files");
    if (mimetype_supported())
    {
        filter->add_mime_type("text/*");
    }
    else
    {
        for (int i = 0; text_globs != NULL && text_globs[i] != NULL; i++)
        {
            const char *glob = text_globs[i];
            filter->add_pattern(glob);
        }
    }
    dialog->add_filter(filter);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any Files");
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);

    dialog->show();
}

void TextEditor::savedialog_response(int response)
{
    if (response == Gtk::RESPONSE_ACCEPT)
    {
        // Get Filename
        auto file = dialog->get_file();
        std::string filename = file->get_path();
        // Get Text
        Glib::ustring text;
        text = buffer1->get_text();
        // Save to a file
        std::ofstream outfile;
        outfile.open(filename, std::ios_base::out);
        outfile << text;
        outfile.close();
    }
    dialog.reset();
}

void TextEditor::buffer1_changed()
{
    // When the text changed,enable the copy button
}

void TextEditor::search_entry_changed()
{
    // Get Text to search
    const Glib::ustring text = search_entry.get_text();

    Gtk::TextIter start, end;
    // If get text to search, select the text and storage the position
    if (text.length() != 0)
    {
        if (buffer1->begin().forward_search(text, Gtk::TEXT_SEARCH_CASE_INSENSITIVE, start, end))
        {
            curr_iter_up = start;
            curr_iter_down = end;
            buffer1->select_range(start, end);
            textview1.scroll_to(start);
        }
    }
}

void TextEditor::search_forward()
{
    // Get Text to search
    const Glib::ustring search_text = search_entry.get_text();

    Gtk::TextIter start, end;
    // Get Text to search, down to the end of text
    if (search_text.length() != 0)
    {
        if (curr_iter_down.forward_search(search_text, Gtk::TEXT_SEARCH_CASE_INSENSITIVE, start, end))
        {
            curr_iter_up = start;
            curr_iter_down = end;
            buffer1->select_range(start, end);
            textview1.scroll_to(start);
        }
    }
}

void TextEditor::search_backward()
{
    // Get Text to search, up to the start of text
    const Glib::ustring search_text = search_entry.get_text();

    Gtk::TextIter start, end;
    // Get Text to search
    if (search_text.length() != 0)
    {
        if (curr_iter_up.backward_search(search_text, Gtk::TEXT_SEARCH_CASE_INSENSITIVE, start, end))
        {
            curr_iter_up = start;
            curr_iter_down = end;
            buffer1->select_range(start, end);
            textview1.scroll_to(start);
        }
    }
}

void TextEditor::btncopy_clicked()
{
    // Get Text
    Glib::ustring text;
    Gtk::TextBuffer::iterator start, end;
    if (buffer1->get_selection_bounds(start, end))
    {
        text = buffer1->get_text(start, end);
    }
    else
    {
        text = buffer1->get_text();
    }

    // Get Clipboard and set text
    auto refClipboard = Gtk::Clipboard::get();
    refClipboard->set_text(text);

    // Show InfoBar
    label1.set_label("The Text is copyed");
    infobar.show();
}

void TextEditor::btnpaste_clicked()
{
    // Get ClipBoard
    auto refClipboard = Gtk::Clipboard::get();
    refClipboard->request_text(sigc::mem_fun(*this, &TextEditor::clipboard_receive));
}

void TextEditor::clipboard_receive(const Glib::ustring &text)
{
    if (buffer1->insert_interactive_at_cursor(text))
    {
        // Show InfoBar
        label1.set_label("The Text is Pasted at cursor position");
        infobar.show();
    }
    else
    {
        // Show InfoBar
        label1.set_label("Text Paste Error!");
        infobar.show();
    }
}

void TextEditor::btnclose_clicked()
{
    buffer1->set_text("");
    file_opened = false;
}

void TextEditor::infobar_response(int response)
{
    infobar.hide();
}

void TextEditor::about_activated()
{
    char *version, *copyright;
    // The Gtkmm Version
    version = g_strdup_printf("1.0\nRunning Against Gtkmm %d.%d.%d",
                              GTKMM_MAJOR_VERSION,
                              GTKMM_MINOR_VERSION,
                              GTKMM_MICRO_VERSION);
    const char *authors[] = {"Dale Clack", NULL};
    // Copyright Informaion
    copyright = g_strdup_printf("© 2019—2022 The Xe Project");
    // Show the about dialog
    gtk_show_about_dialog(GTK_WINDOW(this->gobj()),
                          "program-name", "Text Editot",
                          "version", version,
                          "copyright", copyright,
                          "comments", "A simple text editor",
                          "authors", authors,
                          "license-type", GTK_LICENSE_GPL_3_0,
                          "logo-icon-name", "org.gtk.daleclack",
                          "title", "About Simple text editor",
                          (char *)NULL);
    // Free memory
    g_free(version);
    g_free(copyright);
}
