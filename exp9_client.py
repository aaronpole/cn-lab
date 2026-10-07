import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect(("127.0.0.1", 5000))

filename = input("Enter filename: ")

client.send(filename.encode())

data = client.recv(4096).decode()

print("\nServer Response:")
print(data)

client.close()