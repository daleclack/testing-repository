#include "FileWindow.hh"
#include <iostream> 

FileWindow::FileWindow()
:parent_str("/"),
vbox(Gtk::ORIENTATION_VERTICAL,5),
btnbox(Gtk::ORIENTATION_HORIZONTAL,5)
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
    m_toolbar.insert(up_button,-1);

    //"Home" Button
    home_button.set_icon_name("go-home");
    home_button.set_is_important();
    m_toolbar.insert(home_button,-1);

    //"New Folder" Button
    new_button.set_icon_name("folder-new");
    new_button.set_is_important();
    m_toolbar.insert(new_button,-1);

    //"Delete" Button
    delete_button.set_icon_name("edit-delete");
    delete_button.set_is_important();
    m_toolbar.insert(delete_button,-1);

    //"View Mode" Button
    view_item.add(view_button);
    view_mode=ViewMode::MODE_ICON;
    view_button.set_relief(Gtk::RELIEF_NONE);
    view_button.set_image_from_icon_name("view-grid-symbolic",Gtk::ICON_SIZE_LARGE_TOOLBAR);
    m_viewbar.insert(view_item,-1);

    //Menu Button
    menu_item.add(menubtn);
    menubtn.set_relief(Gtk::RELIEF_NONE);
    m_viewbar.insert(menu_item,-1);
    m_viewbar.set_toolbar_style(Gtk::TOOLBAR_ICONS);

    //Create Store
    m_liststore = Gtk::ListStore::create(columns);
    m_liststore->set_default_sort_func(sigc::mem_fun(*this,&FileWindow::sort_func));
    m_liststore->set_sort_column(-1,Gtk::SORT_ASCENDING);
    fill_store();

    create_views();
    vbox.pack_start(m_sw);
    m_sw.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    m_sw.add(stack);

    show_all_children();
}

int FileWindow::sort_func(const Gtk::TreeModel::iterator &a,const Gtk::TreeModel::iterator &b){
    bool is_dir_a,is_dir_b;
    Glib::ustring name_a,name_b;

    auto row_a=*a,row_b=*b;
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

            if(dir_name != ""){
                auto row=*(m_liststore->append());
                row[columns.m_col_display_name] = display_name;
                row[columns.m_col_is_dir] = is_dir;
                row[columns.m_col_path] = std::string(path);
                row[columns.m_col_pixbuf] = is_dir ? folder_pixbuf : file_pixbuf;
            }

            g_free(path);

        }while(dir_name != "");
    }
    catch(const Glib::Error &ex){
        std::cout << ex.what() << std::endl;
    } 
}

void FileWindow::create_views(){
    //Initalize IconView
    m_iconview.set_model(m_liststore);
    m_iconview.set_text_column(columns.m_col_display_name);
    m_iconview.set_pixbuf_column(columns.m_col_pixbuf);
    m_iconview.signal_item_activated().connect(sigc::mem_fun(*this,&FileWindow::item_activated));

    stack.add(m_iconview);
    stack.add(m_treeview);
}

void FileWindow::item_activated(const Gtk::TreePath &path){
    auto row = *(m_liststore->get_iter(path));
    bool is_dir;
    Glib::ustring path_name;

    path_name = row[columns.m_col_path];
    is_dir = row[columns.m_col_is_dir];

    if(!is_dir){return ;}

    parent_str = path_name;

    fill_store();
}
