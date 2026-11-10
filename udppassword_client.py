import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
p = input("Enter password: ")
s.sendto(p.encode(), ("127.0.0.1", 5000))
data, addr = s.recvfrom(1024)
print(data.decode())
s.close()
