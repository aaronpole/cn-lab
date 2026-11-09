import socket, threading, os

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("127.0.0.1", 5000))

def handle(name, addr):
    if os.path.isfile(name):
        with open(name, "r") as f:
            msg = f"PID: {os.getpid()}\n" + f.read()
    else:
        msg = "File not found"

    s.sendto(msg.encode(), addr)

print("UDP File Server Started")

while True:
    data, addr = s.recvfrom(1024)
    name = data.decode()
    threading.Thread(target=handle, args=(name, addr)).start()
