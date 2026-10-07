import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_address = ("127.0.0.1", 5000)

message = input("Enter a message: ")

client_socket.sendto(message.encode(), server_address)

data, address = client_socket.recvfrom(1024)

print("Original message:", message)
print("Translated message:", data.decode())

client_socket.close()