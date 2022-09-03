mkdir ~/.local/share/icons/hicolor/scalable/apps
mkdir ~/.local/share/icons/hicolor/symbolic/apps
cp ./org.gtk.daleclack.png ~/.local/share/icons/hicolor/48x48/apps/org.gtk.daleclack.png
cp ./org.gtk.daleclack.svg ~/.local/share/icons/hicolor/scalable/apps/org.gtk.daleclack.svg
cp ./org.gtk.daleclack.svg ~/.local/share/icons/hicolor/symbolic/apps/org.gtk.daleclack.svg
cp ./org.gtk.daleclack.desktop ~/.local/share/applications
gtk-update-icon-cache -f -t ~/.local/share/icons/hicolor
gtk4-update-icon-cache -f -t ~/.local/share/icons/hicolor
