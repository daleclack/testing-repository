#include "FileWindow.hh"
#include <iostream> 

FileWindow::FileWindow()
:parent_str("/"),
vbox(Gtk::ORIENTATION_VERTICAL,5),
btnbox(Gtk::ORIENTATION_HORIZONTAL,5),
menubox(Gtk::ORIENTATION_VERTICAL,5),
show_hidden("Show hidden files")
{
    //Initalize Window
    set_default_size(650,400);
    set_icon_name("org.gtk.daleclack");
    set_title("File Manager");

    //Load Pixbufs
    file_pixbuf=Gdk::Pixbuf::create_from_resource("/org/gtk/daleclack/gnome-fs-regular.png");
    folder_pixbuf=Gdk::Pixbuf::create_from_resource("/org/gtk/daleclack/gnome-fs-directory.png");

    //Create Child Widgets
    vbox.pack_start(btnbox,Gtk::PACK_SHRINK);
    add(vbox);

    m_toolbar.set_toolbar_style(Gtk::TOOLBAR_ICONS);
    btnbox.pack_start(m_toolbar,Gtk::PACK_SHRINK);
    btnbox.pack_end(m_viewbar,Gtk::PACK_SHRINK);

    //"Up" Button
    up_button.set_icon_name("go-up");
    up_button.set_is_important();
    up_button.set_sensitive(false);
    up_button.signal_clicked().connect(sigc::mem_fun(*this,&FileWindow::btnup_clicked));
    m_toolbar.insert(up_button,-1);

    //"Home" Button
    home_button.set_icon_name("go-home");
    home_button.set_is_important();
    home_button.signal_clicked().connect(sigc::mem_fun(*this,&FileWindow::btnhome_clicked));
    m_toolbar.insert(home_button,-1);

    //"New Folder" Button
    new_button.set_icon_name("folder-new");
    new_button.set_is_important();
    new_button.signal_clicked().connect(sigc::mem_fun(*this,&FileWindow::btnnew_clicked));
    m_toolbar.insert(new_button,-1);

    //"Delete" Button
    delete_button.set_icon_name("edit-delete");
    delete_button.set_is_important();
    delete_button.signal_clicked().connect(sigc::mem_fun(*this,&FileWindow::btndel_clicked));
    m_toolbar.insert(delete_button,-1);

    //"View Mode" Button
    view_item.add(view_button);
    view_mode=ViewMode::MODE_ICON;
    view_button.set_relief(Gtk::RELIEF_NONE);
    view_button.set_image_from_icon_name("view-grid-symbolic",Gtk::ICON_SIZE_LARGE_TOOLBAR);
    view_button.signal_clicked().connect(sigc::mem_fun(*this,&FileWindow::btnview_clicked));
    m_viewbar.insert(view_item,-1);

    //Menu Button
    menu_item.add(menubtn);
    menubtn.set_relief(Gtk::RELIEF_NONE);
    m_viewbar.insert(menu_item,-1);
    m_viewbar.set_toolbar_style(Gtk::TOOLBAR_ICONS);
    show_hidden.set_active(false);
    show_hidden.signal_clicked().connect(sigc::mem_fun(*this,&FileWindow::btnhide_clicked));
    menubox.pack_start(show_hidden,Gtk::PACK_SHRINK);
    popover.add(menubox);
    menubtn.set_popover(popover);
    popover.show_all_children();

    //Info Bar
    m_infobar.add_button("OK",Gtk::RESPONSE_OK);
    auto pbox = dynamic_cast<Gtk::Container*>(m_infobar.get_content_area());
    pbox->add(info_label);
    vbox.pack_start(m_infobar,Gtk::PACK_SHRINK);
    m_infobar.signal_response().connect(sigc::mem_fun(*this,&FileWindow::infobar_response));

    //Create Store
    m_liststore = Gtk::ListStore::create(columns);
    m_liststore->set_default_sort_func(sigc::mem_fun(*this,&FileWindow::sort_func));
    m_liststore->set_sort_column(-1,Gtk::SORT_ASCENDING);
    fill_store();

    initalize_views();
    m_sw.add(stack);
    vbox.pack_start(m_sw);
    
    show_all_children();
    m_infobar.hide();
}

int FileWindow::sort_func(const Gtk::TreeModel::iterator &a,const Gtk::TreeModel::iterator &b){
    bool is_dir_a,is_dir_b;
    Glib::ustring name_a,name_b;

    auto row_a= *a,row_b= *b;
    is_dir_a = row_a[columns.m_col_is_dir];
    is_dir_b = row_b[columns.m_col_is_dir];
    name_a = row_a[columns.m_col_display_name];
    name_b = row_b[columns.m_col_display_name];

    if(!is_dir_a && is_dir_b){
        return 1;
    }
    if(is_dir_a && !is_dir_b){
        return -1;
    }
    if(name_a[0] != '.' && name_b[0] == '.'){
        return 1;
    }
    if(name_a[0] == '.' && name_b[0] != '.'){
        return -1;
    }else{
        return g_utf8_collate(name_a.c_str(),name_b.c_str());
    }
}

void FileWindow::fill_store(){
    Gtk::TreeModel::iterator iter;

    //Clear the store
    m_liststore->clear();

    //Go through the directory and get information
    try{
        Glib::Dir dir1(parent_str);
        bool is_dir;
        Glib::ustring display_name;
        std::string dir_name;
        /* Ignore the files start with '.' when the button is not toggled */
        do{
            dir_name = dir1.read_name();
            //std::cout<<dir_name<<std::endl;

            char * path = g_build_filename(parent_str.c_str(),dir_name.c_str(),NULL);
            is_dir = Glib::file_test(path,Glib::FILE_TEST_IS_DIR);
            display_name = Glib::filename_to_utf8(dir_name);

            if(dir_name[0] == '.' && !show_hidden.get_active()){
                continue;
            }

            if(dir_name != ""){
                auto row=*(m_liststore->append());
                row[columns.m_col_display_name] = display_name;
                row[columns.m_col_is_dir] = is_dir;
                row[columns.m_col_path] = Glib::ustring(path);
                row[columns.m_col_pixbuf] = is_dir ? folder_pixbuf : file_pixbuf;
            }

            g_free(path);

        }while(dir_name != "");
    }
    catch(const Glib::Error &ex){
        std::cout << ex.what() << std::endl;
        parent_str = tmp_str;
        fill_store();
    } 
}

void FileWindow::initalize_views(){
    //Initalize IconView
    m_iconview.set_model(m_liststore);
    m_iconview.set_text_column(columns.m_col_display_name);
    m_iconview.set_pixbuf_column(columns.m_col_pixbuf);
    m_iconview.set_selection_mode(Gtk::SELECTION_MULTIPLE);
    m_iconview.signal_item_activated().connect(sigc::mem_fun(*this,&FileWindow::item_activated));
    m_iconview.set_row_spacing(0);

    //Initalize TreeView
    m_treeview.set_model(m_liststore);
    m_treeview.append_column("",columns.m_col_pixbuf);
    m_treeview.append_column("Name",columns.m_col_display_name);
    m_treeview.signal_row_activated().connect(sigc::mem_fun(*this,&FileWindow::row_activated));

    stack.add(m_iconview);
    stack.add(m_treeview);
}

void FileWindow::item_activated(const Gtk::TreePath &path){
    auto row = *(m_liststore->get_iter(path));
    bool is_dir;
    Glib::ustring path_name;

    //Backup current parent dir
    tmp_str = parent_str;

    //Get Path Name and read
    path_name = row[columns.m_col_path];
    is_dir = row[columns.m_col_is_dir];

    if(!is_dir){return ;}

    parent_str = path_name;

    fill_store();
    up_button.set_sensitive();
}

void FileWindow::row_activated(const Gtk::TreePath &path,Gtk::TreeViewColumn * sel_column){
    auto row = *(m_liststore->get_iter(path));
    bool is_dir;
    Glib::ustring path_name;

    //Backup current parent dir
    tmp_str = parent_str;

    //Get Path Name and read
    path_name = row[columns.m_col_path];
    is_dir = row[columns.m_col_is_dir];

    if(!is_dir){return ;}

    parent_str = path_name;

    fill_store();
    up_button.set_sensitive();
}

void FileWindow::btnup_clicked(){
    //Go to upper dir
    Glib::ustring dir_name;
    dir_name = Glib::path_get_dirname(parent_str);
    parent_str = dir_name;
    fill_store();
}

void FileWindow::btnhome_clicked(){
    //Go to home dir
    parent_str = Glib::ustring(Glib::get_home_dir());
    fill_store();
}

void FileWindow::btnnew_clicked(){
    //Create Dialog
    Gtk::Dialog * dialog = new Gtk::Dialog("Create a folder",*this,Gtk::DIALOG_USE_HEADER_BAR);
    dialog->add_button("OK",Gtk::RESPONSE_OK);
    dialog->set_default_response(Gtk::RESPONSE_OK);

    //Add Entry
    Gtk::Box * pbox = dialog->get_content_area();
    pbox->add(entry_file);
    entry_file.set_activates_default();

    dialog->signal_response().connect(sigc::bind(sigc::mem_fun(*this,&FileWindow::dialog_response),dialog));
    dialog->show_all();
}

void FileWindow::btndel_clicked(){
    Glib::ustring tmp;
    switch(view_mode){
        case ViewMode::MODE_ICON:
            {   
            auto selected_items = m_iconview.get_selected_items();
                for(auto it = selected_items.begin();it != selected_items.end(); it++){
                    auto row = *(m_liststore->get_iter(*it));
                    tmp = row[columns.m_col_path] + " delete failed!";
                    info_label.set_text(tmp);
                    m_infobar.show();
                }
                selected_items.clear();
            }
            break;
        case ViewMode::MODE_LIST:
            {
                auto selected_item = m_treeview.get_selection();
                auto row = *(selected_item->get_selected());
                tmp = row[columns.m_col_path] + " delete failed!";
                info_label.set_text(tmp);
                m_infobar.show();
                selected_item.reset();
            }
            break;
    }
}

void FileWindow::btnview_clicked(){
    switch(view_mode){
        case ViewMode::MODE_ICON:
            stack.set_visible_child(m_treeview);
            view_button.set_image_from_icon_name("view-list-symbolic",Gtk::ICON_SIZE_LARGE_TOOLBAR);
            view_mode = ViewMode::MODE_LIST;
            break;
        case ViewMode::MODE_LIST:
            stack.set_visible_child(m_iconview);
            view_button.set_image_from_icon_name("view-grid-symbolic",Gtk::ICON_SIZE_LARGE_TOOLBAR);
            view_mode = ViewMode::MODE_ICON;
            break;
    }
}

void FileWindow::infobar_response(int response_id){
    m_infobar.hide();
}

void FileWindow::dialog_response(int response_id,Gtk::Dialog * dialog){
    if(response_id == Gtk::RESPONSE_OK){
        Glib::ustring folder_name = entry_file.get_text();
        if(parent_str.length() == 1 && parent_str[0] == '/'){
            folder_name = parent_str + folder_name;
        }else{
            folder_name = parent_str + "/" + folder_name;
        }
        if(g_mkdir_with_parents(folder_name.c_str(),0755) == -1){
            std::cout<<"Error Occured"<<std::endl;
        }else{
            fill_store();
        }
    }
    delete dialog;
}

void FileWindow::btnhide_clicked(){
    fill_store();
}

FileWindow::~FileWindow(){
    folder_pixbuf.reset();
    file_pixbuf.reset();
}
