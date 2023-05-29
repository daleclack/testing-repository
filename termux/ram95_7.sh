pulseaudio -D
export PULSE_SERVER=tcp:127.0.0.1:4713
qemu-system-x86_64 -accel tcg,thread=multi -m size=512M -vga std -vnc :1  -cdrom '/sdcard/0/Ram95_7.iso' -boot d -device sb16
