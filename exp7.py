import socket
import threading

clients = []

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

host = "127.0.0.1"
port = 5000

server.bind((host, port))
server.listen()

print("Chat Server Started...")
print("Waiting for clients...")

def broadcast(message, sender):
    for client in clients:
        if client != sender:
            try:
                client.send(message)
            except:
                clients.remove(client)

def handle_client(client):
    while True:
        try:
            message = client.recv(1024)

            if not message:
                break

            print(message.decode())
            broadcast(message, client)

        except:
            break

    if client in clients:
        clients.remove(client)

    client.close()

while True:
    client, address = server.accept()

    print("Client connected:", address)

    clients.append(client)

    thread = threading.Thread(
        target=handle_client,
        args=(client,)
    )

    thread.start()