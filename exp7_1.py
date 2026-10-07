import socket
import threading

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect(("127.0.0.1", 5000))

name = input("Enter your name: ")

print("Connected to chat server.")
print("Type messages below.")

def receive_messages():
    while True:
        try:
            message = client.recv(1024).decode()

            if message:
                print("\n" + message)

        except:
            break

thread = threading.Thread(
    target=receive_messages,
    daemon=True
)

thread.start()

while True:
    message = input()

    if message.lower() == "exit":
        break

    message = name + ": " + message

    client.send(message.encode())

client.close()