#include "MyWin.hh"
#include <cstdlib>
#include <cstdio>

MyWin::MyWin()
:vbox(Gtk::ORIENTATION_VERTICAL,5),
entrybox1(Gtk::ORIENTATION_HORIZONTAL,5),
entrybox2(Gtk::ORIENTATION_HORIZONTAL,5),
row_label("Rows:"),
col_label("Cols:"),
btn_ok("OK")
{
    set_icon_name("org.gtk.daleclack");
    //Initalize entrys
    row_entry.set_text("14");
    col_entry.set_text("14");
    //Pack entrys and labels
    entrybox1.pack_start(row_label);
    entrybox1.pack_start(row_entry);
    entrybox2.pack_start(col_label);
    entrybox2.pack_start(col_entry);
    vbox.pack_start(entrybox1);
    vbox.pack_start(entrybox2);
    //Window1 Initalize
    window1.set_icon_name("org.gtk.daleclack");
    window1.set_default_size(505,495);
    window1.add(sw);
    //The "OK" button
    vbox.pack_start(btn_ok);
    btn_ok.signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnok_clicked));
    add(vbox);
    show_all_children();
}

void MyWin::btnok_clicked(){
    Glib::ustring row_str,col_str;
    int rows,cols,index=0,j;
    //Get Row and column setting in entry
    row_str=row_entry.get_text();
    col_str=col_entry.get_text();
    rows=atoi(row_str.c_str());
    cols=atoi(col_str.c_str());
    //If window is not empty,remove child
    if(sw.get_child()){
        sw.remove();
        delete grid1;
    }
    //Create button
    grid1=new Gtk::Grid;
    for(int i=0;i<rows;i++){
        for(j=0;j<cols;j++){
            pBtn=new MyBtn;
            //pBtn->set_size_request(20,20);
            pBtn->row=i;
            pBtn->col=j;
            pBtn->signal_clicked().connect(sigc::bind<MyBtn*>(sigc::mem_fun(*this,&MyWin::pbtn_clicked),pBtn));
            grid1->attach(*pBtn,j,i);
        }
        index=j;
    }
    sw.add(*grid1);
    window1.show_all();
}

void MyWin::pbtn_clicked(MyBtn *pBtn1){
    freopen("test.txt","a",stdout);
    g_print("%d %d\n",pBtn1->row,pBtn1->col);
    fclose(stdout);
}

MyWin::~MyWin(){

}
