import socket
import threading

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 5000))

name = input("Enter name: ")

def receive():
    while True:
        try:
            msg = s.recv(1024).decode()
            if not msg:
                break
            print("\n" + msg)
        except:
            break

threading.Thread(target=receive, daemon=True).start()

while True:
    msg = input()
    if msg.lower() == "exit":
        break
    s.sendall((name + ": " + msg).encode())

s.close()
