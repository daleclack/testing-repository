cd /sdcard/0
qemu-system-x86_64 -hda '/sdcard/0/Cpp.vhd' -m size=256M -vga std -vnc :1 -usb -device usb-tablet -cdrom '/sdcard/0/win31_Ram2.iso' -boot d -device sb16
