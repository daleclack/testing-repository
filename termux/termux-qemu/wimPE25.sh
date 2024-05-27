# Options:
# -m Random Access Memory
# -cpu for cpu type
# -smp for core count
# -M q35 for sata bus
# -accel for acceleration
# -drive for disk/cdrom
# -boot for boot device:a-floppy,c-disk,fd-cdrom
# -vnc for vnc display
# -usb -device usb-tablet for fix mouse
cd /sdcard/0
# start qemu
qemu-system-x86_64 \
-m 768 \
-cpu max \
-M pc \
-accel tcg,thread=multi \
-drive file=Pagefile.vhd,media=disk \
-drive file=Cpp.vhd,media=disk \
-drive file=wimPE25.iso,media=cdrom \
-drive file=music_disc.iso,media=cdrom \
-boot d \
-vnc :1
# -usb -device usb-tablet
