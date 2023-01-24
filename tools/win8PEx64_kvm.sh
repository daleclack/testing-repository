echo 'The qemu start shell script by Dale Clack'
echo 'kvm acceleration is needed'
# qemu options:
# -m for the readom access memory
# -smp for cpu cores
# -M for machine type, q35 for ahci disk controller
# -accel for acceleration
# -cpu for cpu type
# -device VGA for display unit, the memory can be changed
# -drive for disks or cdrom
# -boot d to boot from cdrom
qemu-system-x86_64 \
-m 2048 \
-smp 6 \
-M q35 \
-accel kvm \
-cpu max \
-device VGA,vgamem_mb=256 \
-usb -device usb-tablet \
-drive file=/mnt/Dell/Download/Cpp.vhd,media=disk \
-drive file=Win8PEx64-5.iso,media=cdrom \
-drive file=Dev-Cpp.iso,media=cdrom \
-boot d