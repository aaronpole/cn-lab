import socket
import threading
import os

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

host = "127.0.0.1"
port = 5000

server.bind((host, port))
server.listen()

print("File Server Started...")
print("Waiting for clients...")


def handle_client(client):
    filename = client.recv(1024).decode()

    print("Requested file:", filename)

    if os.path.exists(filename):
        with open(filename, "r") as file:
            content = file.read()

        pid = os.getpid()

        response = f"Server PID: {pid}\n\n{content}"
    else:
        response = "Error: File does not exist."

    client.send(response.encode())
    client.close()


while True:
    client, address = server.accept()

    print("Client connected:", address)

    thread = threading.Thread(
        target=handle_client,
        args=(client,)
    )

    thread.start()