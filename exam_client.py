import socket 
s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
exp = input("Enter expression : ")
s.sendto(exp.encode(),("127.0.0.1",5000))
result, _ = s.recvfrom(1024)
print(result.decode())