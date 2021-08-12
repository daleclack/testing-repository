#include "MyWin.hh"

MyWin::MyWin()
:main_box(Gtk::ORIENTATION_HORIZONTAL,5),
btn_box(Gtk::ORIENTATION_VERTICAL,5),
m_label("No Selection"),
btn_load("Load Config"),
btn_save("Save Config"),
btn_exit("Exit")
{
    //Initalize window
    set_icon_name("org.gtk.daleclack");
    set_default_size(400,300);

    //Add Widgets
    scrolled.add(m_treeview);
    scrolled.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    main_box.pack_start(scrolled);

    //Buttons
    btn_box.pack_start(m_label,Gtk::PACK_SHRINK);
    btn_box.pack_start(btn_load,Gtk::PACK_SHRINK);
    btn_box.pack_start(btn_save,Gtk::PACK_SHRINK);
    btn_box.pack_start(btn_exit,Gtk::PACK_SHRINK);
    btn_box.set_valign(Gtk::ALIGN_CENTER);
    main_box.pack_start(btn_box,Gtk::PACK_SHRINK);

    add(main_box);

    //Create and add model
    ref_liststore=Gtk::ListStore::create(m_columns);
    m_treeview.set_model(ref_liststore);

    m_treeview.append_column_editable("Key",m_columns.m_col_key);
    m_treeview.append_column_editable("Value",m_columns.m_col_value);

    selection=m_treeview.get_selection();

    btn_exit.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::hide));
    btn_save.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnsave_clicked));
    btn_load.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnload_clicked));
    selection->signal_changed().connect(sigc::mem_fun(*this,&MyWin::selection_changed));

    show_all_children();
}

void MyWin::selection_changed(){
    auto row=*(selection->get_selected());
    m_label.set_label(row[m_columns.m_col_value]);
}

void MyWin::btnload_clicked(){
    dialog=Gtk::FileChooserNative::create("Open A Config File",*this,Gtk::FILE_CHOOSER_ACTION_OPEN,
            "OK","Cancel");

    dialog->signal_response().connect(sigc::mem_fun(*this,&MyWin::dialog_response));

    auto filter_any=Gtk::FileFilter::create();
    filter_any->add_pattern("*");
    filter_any->set_name("Any Files");

    dialog->add_filter(filter_any);

    dialog->show();
}

void MyWin::dialog_response(int response_id){
    if(response_id==Gtk::RESPONSE_ACCEPT){
       auto filename=dialog->get_filename();

        //Clear the liststore
        ref_liststore->clear();

        //If Configs is not empty,clear it
        if(!my_configs.empty()){
            my_configs.clear();
        }

        if(readCfgFile(filename,my_configs)){
            auto mite=my_configs.begin();
            for(;mite!=my_configs.end();mite++){
                auto row=*(ref_liststore->append());
                row[m_columns.m_col_key]=mite->first;
                row[m_columns.m_col_value]=mite->second;
            }
        } 
    }
    dialog.reset();
}

void MyWin::btnsave_clicked(){
    dialog=Gtk::FileChooserNative::create("Open A Config File",*this,Gtk::FILE_CHOOSER_ACTION_SAVE,
            "OK","Cancel");

    dialog->signal_response().connect(sigc::mem_fun(*this,&MyWin::dialog_save_response));

    auto filter_cfg=Gtk::FileFilter::create();
    filter_cfg->add_pattern("*.cfg");
    filter_cfg->set_name("Config Files");
    dialog->add_filter(filter_cfg);

    auto filter_any=Gtk::FileFilter::create();
    filter_any->add_pattern("*");
    filter_any->set_name("Any Files");
    dialog->add_filter(filter_any);

    dialog->show();
}

void MyWin::dialog_save_response(int response_id){
    if(response_id==Gtk::RESPONSE_ACCEPT){

        //Get Filename and open(create) a config file
        std::string filename=dialog->get_filename();
        std::fstream outfile;
        outfile.open(filename,std::ios_base::out);
        if(!outfile.is_open()){
            dialog.reset();
            std::cout<<"Error!";
            return ;
        }

        //Write Key and Values
        auto children=ref_liststore->children();
        for(auto iter = children.begin();
            iter != children.end(); iter++)
        {
            auto row=*iter;
            outfile<<row[m_columns.m_col_key]<<"="<<row[m_columns.m_col_value]<<std::endl;
        }

        //Close the config file
        outfile.close();

    }
    dialog.reset();
}
