#include "MyWin.hh"
#include <iostream>

MyWin::MyWin()
:m_vbox(Gtk::ORIENTATION_VERTICAL,0),
btn_quit("Exit"),
btn_add("Add Item"),
btn_del("Delete Item")
{
    //Initalize window
    set_icon_name("org.gtk.daleclack");
    set_default_size(400,300);
    set_title("TreeView Test1");

    //Add widgets
    add(m_vbox);
    sw.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    sw.add(m_treeview);
    m_vbox.pack_start(sw);

    //Create the store
    ref_liststore=Gtk::ListStore::create(m_columns);
    m_treeview.set_model(ref_liststore);
    m_treeview.set_headers_visible(false);

    //Append items
    row=*(ref_liststore->append());
    row[m_columns.m_col_text]="List 1";

    row=*(ref_liststore->append());
    row[m_columns.m_col_text]="List 2";

    row=*(ref_liststore->append());
    row[m_columns.m_col_text]="List 3";

    m_treeview.append_column("List",m_columns.m_col_text);

    //Add a Entry
    m_vbox.pack_start(m_entry,Gtk::PACK_SHRINK);

    //Show item button
    btn_del.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btndel_clicked));
    m_buttonbox.pack_start(btn_del,Gtk::PACK_SHRINK);

    //"Add Item" button
    btn_add.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnadd_clicked));
    m_buttonbox.pack_start(btn_add,Gtk::PACK_SHRINK);
    //"Exit" button
    btn_quit.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::on_btnquit_clicked));
    m_buttonbox.pack_end(btn_quit,Gtk::PACK_SHRINK);
    m_vbox.pack_end(m_buttonbox,Gtk::PACK_SHRINK);
    
    //Show all widgets
    show_all_children();
}

void MyWin::on_btnquit_clicked(){
    hide();
}

void MyWin::btndel_clicked(){
    //Delete the iter that selected
    ref_selection=m_treeview.get_selection();
    Gtk::TreeModel::iterator iter=ref_selection->get_selected();
    if(iter){
        ref_liststore->erase(iter);
    }
}

void MyWin::btnadd_clicked(){
    //Add an Item
    Glib::ustring str;
    str=m_entry.get_text();
    row=*(ref_liststore->append());
    row[m_columns.m_col_text]=str;
}

MyWin::~MyWin(){

}
