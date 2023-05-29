pulseaudio -D
export PULSE_SERVER=tcp:127.0.0.1:4713
qemu-system-x86_64 -m size=512M -accel tcg,thread=multi -vga std -usb -device usb-tablet -vnc :1  -cdrom '/sdcard/0/w3pe91.iso' -boot d -device ac97
