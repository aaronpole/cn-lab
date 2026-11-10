import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 5000))
a = input("Enter first word: ")
b = input("Enter second word: ")
s.sendall((a + " " + b).encode())
print("Result:", s.recv(1024).decode())
s.close()
