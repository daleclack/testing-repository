watch -n1 'echo "scale=2; $(sudo rdmsr 0x198 -u --bitfield 47:32)/8192" | bc >> core_voltage.txt'
