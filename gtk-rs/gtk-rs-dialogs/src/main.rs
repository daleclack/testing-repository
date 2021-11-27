use gtk::prelude::*;
use gtk::{self,Application, ApplicationWindow, Button};
use gtk::glib::clone;

use std::rc::Rc;

fn main() {
    //Create a new application
    let app = Application::builder()
              .application_id("org.gtk.daleclack")
              .build();
    
    //Connect the signal
    app.connect_activate(build_ui);

    //Start the application
    app.run();
}

fn build_ui(app: &Application){
    let window = Rc::new(
                 ApplicationWindow::builder()
                 .application(app)
                 .title("gtk-rs dialogs")
                 .build()
    );
    
    window.set_default_size(800,450);

    let button = Button::builder()
                 .label("Dialog")
                 .halign(gtk::Align::Center)
                 .valign(gtk::Align::Center)
                 .build();

    // Connect callback
    button.connect_clicked(clone!(@strong window =>
        move|_|{
            gtk::glib::MainContext::default().spawn_local(dialog(Rc::clone(&window)));
        }
    ));

    //Create overlay and add a button
    let overlay = gtk::Overlay::new();
    overlay.add_overlay(&button);

    //Create a background
    let background = gtk::Picture::new();
    overlay.set_child(Some(&background));

    window.set_child(Some(&overlay));

    window.present();
}

async fn dialog<W: IsA<gtk::Window>>(window: Rc<W>){
    let file_dialog = gtk::FileChooserDialog::builder()
                      .transient_for(&*window)
                      .use_header_bar(1)
                      .build();

    file_dialog.add_button("OK",gtk::ResponseType::Ok);
    file_dialog.add_button("Cancel",gtk::ResponseType::Cancel);

    file_dialog.connect_response(dialog_responsed);
    
    file_dialog.show();
}

fn dialog_responsed(dialog : &gtk::FileChooserDialog,response_id: gtk::ResponseType){
    if response_id == gtk::ResponseType::Ok {
        //Get FileName
        let file = dialog.file();
        let filename = file.unwrap().path().unwrap();

        //Get Background widget
        let win = dialog.transient_for().unwrap();
        let overlay = win.child().unwrap().dynamic_cast::<gtk::Overlay>().unwrap();
        let background = overlay.child().unwrap().dynamic_cast::<gtk::Picture>().unwrap();
        background.set_filename(filename);

        //println!("{:?}",filename);
    }
    dialog.destroy();
}
