import socket, threading
from datetime import datetime

def handle(c, addr):
    start = datetime.now()
    print("Start:", addr, start)
    try:
        a, b = c.recv(1024).decode().split()
        result = "Anagrams" if sorted(a.lower()) == sorted(b.lower()) else "Not Anagrams"
        c.sendall(result.encode())
    finally:
        print("End:", addr, datetime.now())
        c.close()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("127.0.0.1", 5000))
s.listen(5)

print("Server Started")

while True:
    c, addr = s.accept()
    threading.Thread(target=handle, args=(c, addr)).start()
