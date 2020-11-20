apt install pulseaudio
echo "load-module modules natives protocol-tcp auth-ip-auth=127.0.0.1" >> ../usr/etc/pulse/default.pa
echo "exit-idle-time = -1" >> ../usr/etc/pulse/daemon.conf
pulseaudio -D #pulseaudio#
export PULSE_SERVER=tcp:127.0.0.1:4713
