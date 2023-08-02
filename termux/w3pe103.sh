pulseaudio -D
export PULSE_SERVER=tcp:127.0.0.1:4713
qemu-system-x86_64 -m size=672M -accel tcg,thread=multi -vga std -vnc :1  -cdrom '/sdcard/0/w3pe103.iso' -boot d -device ac97
