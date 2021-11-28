use gtk::{self, prelude::*, glib::clone
    ,glib::{self},gio::{self}};
use std::rc::Rc;

fn main() {
    //Create a application and run
    let app = gtk::Application::builder()
              .application_id("org.gtk.daleclack")
              .build();
    
    //Connect the "activate" signal
    app.connect_activate(build_ui);

    //Start the application
    app.run();
}

fn build_ui(app: &gtk::Application){
    //Create a application window
    let window = Rc::new(gtk::ApplicationWindow::builder()
                        .application(app)
                        .icon_name("org.gtk.daleclack")
                        .title("gtk-rs media player")
                        .build()
                        );
    
    window.set_default_size(800,450);

    //Add a header bar
    let button = gtk::Button::with_label("Open File");
    button.connect_clicked(clone!(@strong window => 
        move |_|{
            glib::MainContext::default().spawn_local(button_clicked(Rc::clone(&window)));
        }
    ));

    let header = gtk::HeaderBar::new();
    header.pack_start(&button);
    window.set_titlebar(Some(&header));

    //Add a video widget
    let video = gtk::Video::new();
    video.set_autoplay(true);

    window.set_child(Some(&video));
    window.present();
}

async fn button_clicked<W:IsA<gtk::Window>>(window: Rc<W>){
    //Create a file dialog
    let file_dialog = gtk::FileChooserDialog::builder()
                      .transient_for(&*window)
                      .use_header_bar(1)
                      .build();

    //Add Buttons
    file_dialog.add_button("OK",gtk::ResponseType::Ok);
    file_dialog.add_button("Cancel",gtk::ResponseType::Cancel);

    //Add Filters
    let file_filter = gtk::FileFilter::new();
    file_filter.set_name(Some(&"Video Files"));
    file_filter.add_mime_type("video/*");

    //Music types
    file_filter.add_pattern("*.mp3");
    file_filter.add_pattern("*.flac");
    file_filter.add_pattern("*.aac");
    file_filter.add_pattern("*.m4a");
    file_dialog.add_filter(&file_filter);

    let filter_any = gtk::FileFilter::new();
    filter_any.set_name(Some(&"Any Files"));
    filter_any.add_pattern("*");
    file_dialog.add_filter(&filter_any);

    //Link Signal
    file_dialog.connect_response(dialog_responsed);
    
    file_dialog.show();
}

fn dialog_responsed(dialog: &gtk::FileChooserDialog,respone_id: gtk::ResponseType){
    if respone_id == gtk::ResponseType::Ok{
        //Get File
        let file = dialog.file().unwrap();

        //Get Video widget
        let win = dialog.transient_for().unwrap();
        let video = win.child().unwrap().dynamic_cast::<gtk::Video>().unwrap();
        video.set_file(None::<&gio::File>);
        video.set_file(Some(&file));
    }
    dialog.destroy();
}
