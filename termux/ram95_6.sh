pulseaudio -D
export PULSE_SERVER=tcp:127.0.0.1:4713
qemu-system-x86_64 -m size=512M -vga std -vnc :1  -cdrom '/sdcard/0/Ram95_6.iso' -boot d -device sb16
