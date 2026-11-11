import socket
from datetime import datetime
s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.bind(("127.0.0.1",5000))
print("UDP Server Started")

while True:
    c, addr = s.recvfrom(1024)
    print("Start : ",addr,datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
    exp = c.decode()
    result = eval(exp)
    s.sendto(str(result).encode(),addr)
    print("End : ",addr,datetime.now().strftime("&Y-%m-%d %H:%M:%S"))