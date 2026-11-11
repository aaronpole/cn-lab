import socket
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client.sendto("TIME".encode(), ("127.0.0.1", 5000))
data, address = client.recvfrom(1024)
print("Request sent: TIME")
print("Server Time:", data.decode())
client.close()