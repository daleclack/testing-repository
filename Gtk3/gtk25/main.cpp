#include <gtk/gtk.h>
#include <cstdlib>
#include <ctime>
#include "360.xpm"

void get_image(GdkPixbuf *dst){
    GdkPixbuf *pixbuf=gdk_pixbuf_new_from_xpm_data(_60);
    static GdkPixbuf *sized=gdk_pixbuf_scale_simple(pixbuf,40,40,GDK_INTERP_BILINEAR);
    dst=sized;
}

struct buttons{
    GtkWidget *button;
    int index;
    char index1[2];
    void init(){
        index1[0]=index+'1';
        button=gtk_button_new_with_label(index1);
        gtk_widget_set_size_request(button,125,125);
    }
};

void test(buttons button1[]){
    gtk_button_set_label(GTK_BUTTON(button1[3].button),"test");
}

int random1(int random_area){
    srand((unsigned)time(NULL));
    int x=rand();
    x%=random_area;
    return x;
}

void Btn_GO_Click(GtkWidget *widget,gpointer data){
    GtkWidget *image1=gtk_image_new_from_pixbuf(image);
    gtk_button_set_image(GTK_BUTTON(button[x].button),image1);
}

static void activate(GtkApplication *app,gpointer user_data){
    GtkWidget *window;
    window=gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"gtk(25)");
    gtk_window_set_default_size(GTK_WINDOW(window),300,450);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

    buttons button[4];
    for(int i=0;i<4;i++){
        button[i].index=i;
        button[i].init();
    }

    GtkWidget *vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    GtkWidget *layout;
    layout=gtk_layout_new(NULL,NULL);

    test(button);
    GtkWidget *label1=gtk_label_new(" ");
    gtk_box_pack_start(GTK_BOX(vbox),label1,FALSE,FALSE,5);
    GtkWidget *label=gtk_label_new("Choose one button");
    gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,5);

    for(int i=0;i<4;i++){
        int tmp=i+1;
        int x=160-145*(tmp%2),y=tmp>2?160:15;
        gtk_layout_put(GTK_LAYOUT(layout),button[i].button,x,y);
    }

    GtkWidget *Btn_GO=gtk_button_new_with_label("GO");
    GtkWidget *Btn_Exit=gtk_button_new_with_label("Exit");
    gtk_widget_set_size_request(Btn_GO,125,50);
    gtk_widget_set_size_request(Btn_Exit,125,50);
    gtk_layout_put(GTK_LAYOUT(layout),Btn_GO,15,305);
    gtk_layout_put(GTK_LAYOUT(layout),Btn_Exit,160,305);
    g_signal_connect_swapped(Btn_Exit,"clicked",G_CALLBACK(gtk_widget_destroy),window);
    g_signal_connect(Btn_GO,"clicked",G_CALLBACK(Btn_GO_Click),NULL);

    gtk_box_pack_start(GTK_BOX(vbox),layout,TRUE,TRUE,5);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    gtk_widget_show_all(window);
}

int main(int argc,char *argv[]){
    GtkApplication *app;
    int status;
    app=gtk_application_new("com.github.gtk25",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    return status;
}
