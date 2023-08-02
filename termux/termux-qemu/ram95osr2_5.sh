pulseaudio -D
export PULSE_SERVER=tcp:127.0.0.1:4713
qemu-system-x86_64 -accel tcg,thread=multi -m size=512M -device VGA,vgamem_mb=32 -vnc :1  -cdrom '/sdcard/0/Ram95OSR2.5.iso' -boot d -device sb16
