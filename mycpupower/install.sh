# Disable cpupower service
sudo systemctl stop cpupower.service
sudo systemctl disable cpupower.service

# Copy my script and service
sudo cp ./mycpupower.service /usr/lib/systemd/system/
sudo cp ./mycpupower /usr/lib/systemd/scripts/

# Enable and start it
sudo systemctl enable mycpupower.service
sudo systemctl start mycpupower.service
