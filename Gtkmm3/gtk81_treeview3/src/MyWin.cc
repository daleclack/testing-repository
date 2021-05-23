#include "MyWin.hh"
#include <iostream>

MyWin::MyWin()
:m_vbox(Gtk::ORIENTATION_VERTICAL,0),
btn_quit("Exit"),
btn_add("Add Item"),
btn_del("Delete Item"),
label_id("ID:"),
label_text("Text:"),
label_percent("Percentage:")
{
    //Initalize window
    set_icon_name("org.gtk.daleclack");
    set_default_size(200,400);
    set_title("TreeView Test1");

    //Add widgets
    add(m_vbox);
    sw.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    sw.add(m_treeview);
    m_vbox.pack_start(sw);

    //Create the store
    ref_liststore=Gtk::ListStore::create(m_columns);
    m_treeview.set_model(ref_liststore);

    //Append items
    row=*(ref_liststore->append());
    row[m_columns.m_col_id]=1;
    row[m_columns.m_col_text]="List 1";
    row[m_columns.m_col_percent]=35;

    row=*(ref_liststore->append());
    row[m_columns.m_col_id]=2;
    row[m_columns.m_col_text]="List 2";
    row[m_columns.m_col_percent]=57;

    row=*(ref_liststore->append());
    row[m_columns.m_col_id]=3;
    row[m_columns.m_col_text]="List 3";
    row[m_columns.m_col_percent]=90;

    //Show Columns
    m_treeview.append_column("ID",m_columns.m_col_id);
    m_treeview.append_column("List",m_columns.m_col_text);

    //Show percent number as a progress bar
    auto cell=Gtk::make_managed<Gtk::CellRendererProgress>();
    cols_count=m_treeview.append_column("Precentages",*cell);
    auto pColumn=m_treeview.get_column(cols_count-1);
    if(pColumn){
        pColumn->add_attribute(cell->property_value(),m_columns.m_col_percent);
    }

    //Add Entries
    m_btnbox_id.pack_start(label_id,Gtk::PACK_SHRINK);
    m_btnbox_id.pack_start(entry_id,Gtk::PACK_EXPAND_PADDING);
    m_btnbox_id.set_homogeneous(false);
    m_btnbox_text.pack_start(label_text,Gtk::PACK_SHRINK);
    m_btnbox_text.pack_start(entry_text,Gtk::PACK_EXPAND_PADDING);
    m_btnbox_text.set_homogeneous(false);
    m_btnbox_percent.pack_start(label_percent,Gtk::PACK_SHRINK);
    m_btnbox_percent.pack_start(entry_percent,Gtk::PACK_EXPAND_PADDING);
    m_btnbox_percent.set_homogeneous(false);

    //Show item button
    btn_del.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btndel_clicked));
    m_buttonbox.pack_start(btn_del,Gtk::PACK_SHRINK);

    //"Add Item" button
    btn_add.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnadd_clicked));
    m_buttonbox.pack_start(btn_add,Gtk::PACK_SHRINK);
    //"Exit" button
    btn_quit.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::on_btnquit_clicked));
    m_buttonbox.pack_end(btn_quit,Gtk::PACK_SHRINK);

    //Pack widgets
    m_vbox.pack_start(m_btnbox_id,Gtk::PACK_SHRINK);
    m_vbox.pack_start(m_btnbox_text,Gtk::PACK_SHRINK);
    m_vbox.pack_start(m_btnbox_percent,Gtk::PACK_SHRINK);
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
    Glib::ustring str,str_id,str_percent;
    int id,percent;

    //Get content
    str_id=entry_id.get_text();
    str=entry_text.get_text();
    str_percent=entry_percent.get_text();
    id=atoi(str_id.c_str());
    percent=atoi(str_percent.c_str());

    //Append item
    row=*(ref_liststore->append());
    row[m_columns.m_col_id]=id;
    row[m_columns.m_col_text]=str;
    row[m_columns.m_col_percent]=percent;
}

MyWin::~MyWin(){

}
