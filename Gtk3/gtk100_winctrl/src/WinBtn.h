#ifndef __WINBTN_H_
#define __WINBTN_H_

#include <gtk/gtk.h>

//Define a type for winbtn
#define WIN_BTN_TYPE (win_btn_get_type())

//WinBtn Type:WinBtn and a window to control
G_DECLARE_FINAL_TYPE(WinBtn,win_btn,WIN,BTN,GtkButton)

WinBtn * win_btn_new(void);

void win_btn_set_application(WinBtn *btn1,GtkApplication *app1);

#endif
