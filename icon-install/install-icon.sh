sudo cp ./org.gtk.daleclack.png /usr/share/icons/hicolor/48x48/apps/org.gtk.daleclack.png
sudo cp ./org.gtk.daleclack.svg /usr/share/icons/hicolor/scalable/apps/org.gtk.daleclack.svg
sudo cp ./org.gtk.daleclack.svg /usr/share/icons/hicolor/symbolic/apps/org.gtk.daleclack.svg
cp ./org.gtk.daleclack.desktop ~/.local/share/applications
sudo gtk-update-icon-cache -f -t /usr/share/icons/hicolor
sudo gtk4-update-icon-cache -f -t /usr/share/icons/hicolor
