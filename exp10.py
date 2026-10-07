import socket
import struct

# Create raw socket
sock = socket.socket(
    socket.AF_INET,
    socket.SOCK_RAW,
    socket.IPPROTO_IP
)

sock.bind(("127.0.0.1", 0))

print("Packet Capturing Started...")
print("Press Ctrl+C to stop.\n")

try:
    while True:
        packet, address = sock.recvfrom(65535)

        # Extract IP header
        ip_header = packet[:20]

        iph = struct.unpack(
            "!BBHHHBBH4s4s",
            ip_header
        )

        source_ip = socket.inet_ntoa(iph[8])
        destination_ip = socket.inet_ntoa(iph[9])
        protocol = iph[6]
        length = iph[2]

        print("Source IP      :", source_ip)
        print("Destination IP :", destination_ip)
        print("Protocol       :", protocol)
        print("Packet Length  :", length)
        print("-" * 35)

except KeyboardInterrupt:
    print("\nPacket capturing stopped.")

finally:
    sock.close()