import socket,threading
from datetime import datetime

s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.bind(("127.0.0.1",5000))

def handle(addr):
    t = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    s.sendto(t.encode(),addr)
print("Server Started")
while True:
    data, address = s.recvfrom(1024)
    threading.Thread(target=handle,args=(address,)).start()