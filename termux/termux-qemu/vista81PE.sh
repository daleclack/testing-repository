qemu-system-x86_64 -hda '/sdcard/0/Pagefile.vhd' -hdb '/sdcard/0/Cpp.vhd' -m size=768M -vga std -vnc :1 -usb -device usb-tablet -cdrom '/sdcard/0/win8PEx64-5.iso' -accel tcg,thread=multi -boot d
