#include "MyWin.hh"
#include <iostream>

MyWin::MyWin()
:m_vbox(Gtk::ORIENTATION_VERTICAL,0),
btn_quit("Exit")
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
    ref_treestore=Gtk::TreeStore::create(m_columns);
    m_treeview.set_model(ref_treestore);
    m_treeview.set_reorderable();

    //Append items
    //Node 1
    row=*(ref_treestore->append());
    row[m_columns.m_col_num]=1;
    row[m_columns.m_col_text]="List 1";

    //Child Nodes
    childrow=*(ref_treestore->append(row.children()));
    childrow[m_columns.m_col_num]=1;
    childrow[m_columns.m_col_text]="Text 1";

    childrow=*(ref_treestore->append(row.children()));
    childrow[m_columns.m_col_num]=2;
    childrow[m_columns.m_col_text]="Text 2";

    //Node 2
    row=*(ref_treestore->append());
    row[m_columns.m_col_num]=2;
    row[m_columns.m_col_text]="List 2";

    //Child Nodes
    childrow=*(ref_treestore->append(row.children()));
    childrow[m_columns.m_col_num]=3;
    childrow[m_columns.m_col_text]="Text 3";

    childrow=*(ref_treestore->append(row.children()));
    childrow[m_columns.m_col_num]=4;
    childrow[m_columns.m_col_text]="Text 4";

    //Node 3
    row=*(ref_treestore->append());
    row[m_columns.m_col_num]=3;
    row[m_columns.m_col_text]="List 3";

    //Child Nodes
    childrow=*(ref_treestore->append(row.children()));
    childrow[m_columns.m_col_num]=5;
    childrow[m_columns.m_col_text]="Text 5";

    m_treeview.append_column("ID",m_columns.m_col_num);
    m_treeview.append_column("List",m_columns.m_col_text);

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

MyWin::~MyWin(){

}
