import socket, threading 
clients = []
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("127.0.0.1", 5000))
s.listen()
print("Chat Server Started")

def broadcast(msg, sender):
    for c in clients:
        if c != sender:
            c.sendall(msg)

def handle(c):
    while True:
        try:
            msg = c.recv(1024)
            if not msg:
                break
            print(msg.decode())
            broadcast(msg, c)
        except:
            break
    clients.remove(c)
    c.close()
while True:
    c, addr = s.accept()
    print("Connected:", addr)
    clients.append(c)
    threading.Thread(target=handle, args=(c,)).start()
