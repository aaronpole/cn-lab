import socket
import threading
from datetime import datetime

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

host = "127.0.0.1"
port = 5000

server.bind((host, port))

print("Time Server Started...")
print("Waiting for requests...")


def handle_client(address):
    current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    server.sendto(
        current_time.encode(),
        address
    )

    print("Time sent to:", address)


while True:
    data, address = server.recvfrom(1024)

    print("Request received from:", address)

    thread = threading.Thread(
        target=handle_client,
        args=(address,)
    )

    thread.start()