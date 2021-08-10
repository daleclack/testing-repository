#include "MyWin.hh"

MyWin::MyWin()
:main_box(Gtk::ORIENTATION_VERTICAL,5),
m_label("No Selection"),
btn_exit("Exit")
{
    //Initalize window
    set_icon_name("org.gtk.daleclack");
    set_default_size(300,400);

    //Add Widgets
    scrolled.add(m_treeview);
    scrolled.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    main_box.pack_start(scrolled);
    main_box.pack_start(m_label,Gtk::PACK_SHRINK);
    main_box.pack_start(btn_exit,Gtk::PACK_SHRINK);
    add(main_box);

    //Create and add model
    ref_liststore=Gtk::ListStore::create(m_columns);
    m_treeview.set_model(ref_liststore);

    //Add Items
    auto row=*(ref_liststore->append());
    row[m_columns.m_col_id]=1;
    row[m_columns.m_col_name]="Name1";
    row[m_columns.m_col_number]="0000000";

    row=*(ref_liststore->append());
    row[m_columns.m_col_id]=2;
    row[m_columns.m_col_name]="Name2";
    row[m_columns.m_col_number]="0000001";

    row=*(ref_liststore->append());
    row[m_columns.m_col_id]=3;
    row[m_columns.m_col_name]="Name3";
    row[m_columns.m_col_number]="0000002";

    m_treeview.append_column_editable("ID",m_columns.m_col_id);
    m_treeview.append_column_editable("Name",m_columns.m_col_name);
    m_treeview.append_column_editable("Number",m_columns.m_col_number);

    selection=m_treeview.get_selection();

    btn_exit.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::hide));
    selection->signal_changed().connect(sigc::mem_fun(*this,&MyWin::selection_changed));

    show_all_children();
}

void MyWin::selection_changed(){
    auto model=*(selection->get_selected());
    m_label.set_label(model[m_columns.m_col_name]);
}
