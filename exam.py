import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
name = input("Enter name of file: ")
s.sendto(name.encode(),("127.0.0.1",5000))
data,addr = s.recvfrom(4096)
print(data.decode())
s.close()