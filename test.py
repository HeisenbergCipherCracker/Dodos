import socket
import fcntl
import struct

def set_ip_address(interface, new_ip):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    packed_ip = socket.inet_aton(new_ip)
    ioctl_result = fcntl.ioctl(s.fileno(), 0x8915, struct.pack('256s', interface.encode('utf-8')))
    s.close()

    return ioctl_result

# Usage
interface_name = "en0"
new_ip_address = "192.168.2.19"

set_ip_address(interface_name, new_ip_address)