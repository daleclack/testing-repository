cd /sdcard/0
export PULSE_SERVER=tcp:127.0.0.1:4713
qemu-system-x86_64 -hda '/sdcard/0/Cpp.vhd' -accel tcg,thread=multi -m size=512M -vga std -vnc :1 -usb -device usb-tablet -cdrom '/sdcard/0/Ram95_4.iso' -boot d -device sb16
