import socket

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_address = ("127.0.0.1", 5000)

message = "TIME"

client.sendto(message.encode(), server_address)

data, address = client.recvfrom(1024)

print("Request sent:", message)
print("Server Time:", data.decode())

client.close()