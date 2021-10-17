#include "FileWindow.hh"

FileWindow::FileWindow()
:vbox(Gtk::ORIENTATION_VERTICAL,5),
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

    show_all_children();
}
