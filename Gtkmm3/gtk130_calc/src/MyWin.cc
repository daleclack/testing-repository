#include "MyWin.hh"
#include "calc.hh"
#include <iostream>

MyWin::MyWin(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &ref_Glade)
    : Gtk::Window(cobject),
      ref_builder(ref_Glade),
      winned(true)
{
    set_icon_name("calcapp");
    set_title("Calculator");

    // Get Widgets
    //ref_builder->get_widget("label_numbers", label_numbers);
    ref_builder->get_widget("entry_ans", entry_ans);
    ref_builder->get_widget("btnanswer", btnanswer);
    ref_builder->get_widget("btnback",btnback);
    ref_builder->get_widget("btnclear",btnclear);
    ref_builder->get_widget("btn0", btns[0]);
    ref_builder->get_widget("btn1", btns[1]);
    ref_builder->get_widget("btn2", btns[2]);
    ref_builder->get_widget("btn3", btns[3]);
    ref_builder->get_widget("btn4", btns[4]);
    ref_builder->get_widget("btn5", btns[5]);
    ref_builder->get_widget("btn6", btns[6]);
    ref_builder->get_widget("btn7", btns[7]);
    ref_builder->get_widget("btn8", btns[8]);
    ref_builder->get_widget("btn9", btns[9]);
    ref_builder->get_widget("btnadd", btns[10]);
    ref_builder->get_widget("btnsubb", btns[11]);
    ref_builder->get_widget("btnmul", btns[12]);
    ref_builder->get_widget("btndiv", btns[13]);
    ref_builder->get_widget("btnleft", btns[14]);
    ref_builder->get_widget("btnright", btns[15]);

    // Link Signals
    btnclear->signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnclear_clicked));
    btnback->signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnback_clicked));
    btnanswer->signal_clicked().connect(sigc::mem_fun(*this,&MyWin::btnanswer_clicked));
    for (int i = 0; i < 16; i++)
    {
        btns[i]->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &MyWin::btns_clicked), btns[i]));
    }
    entry_ans->signal_grab_focus().connect(sigc::mem_fun(*this, &MyWin::entry_ans_focus));
}

void MyWin::btns_clicked(Gtk::Button *button)
{
    // Get Original text and add number from button

    // 1.Get text buffer for insert
    auto buffer = entry_ans->get_buffer();

    // 2.Get text to insert
    Glib::ustring label = button->get_label();

    if (focused)
    {
        pos = entry_ans->get_position();
    }

    // 3.Get Position
    buffer->insert_text(pos, label);
    pos++;
    focused = false;
}

void MyWin::entry_ans_focus()
{
    focused = true;
}

void MyWin::btnclear_clicked(){
    // Clear the text
    entry_ans->set_text("");
}

void MyWin::btnback_clicked(){
    // Get Original text and add number from button

    // 1.Get text buffer for insert
    auto buffer = entry_ans->get_buffer();

    // 2.Get Position to delete
    if (focused)
    {
        pos = entry_ans->get_position();
    }

    // std::cout<<pos<<std::endl;
    pos--;

    // 3.Delete text in the position of cursor
    buffer->delete_text(pos,1);
    focused = false;
}

void MyWin::btnanswer_clicked(){
    // Get expression
    Glib::ustring text = entry_ans->get_text();
    //std::cout<<text<<std::endl;

    // Calculation
    int result = calc_expression_value(text.c_str());
    char result_str[40];
    sprintf(result_str,"%d",result);
    entry_ans->set_text(Glib::ustring(result_str));
}

MyWin *MyWin::create()
{
    // Create a new window
    MyWin *window = nullptr;
    auto builder = Gtk::Builder::create_from_resource("/org/gtk/daleclack/window.ui");
    builder->get_widget_derived("window", window);

    return window;
}
