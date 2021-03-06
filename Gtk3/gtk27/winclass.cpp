#include "winclass.h"
#include "GtkClass.h"

void GtkMain::init(GtkApplication *app){
    GtkWin window;
    Winheader header;
    Winlayout layout;

    window.main_window=gtk_application_window_new(app);
    window.win_init(400,300);

    header.header_init();
    window.set_titlebar(header.header);

    window.add_widget(layout.layout);
    window.show_all();
};
