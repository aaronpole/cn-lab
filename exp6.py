import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

host = "127.0.0.1"
port = 5000

server_socket.bind((host, port))

print("UDP Server is running...")
print("Waiting for client message...")

abbreviations = {
    "btw": "by the way",
    "idk": "I do not know",
    "atm": "at the moment",
    "irl": "in real life",
    "lol": "laughing out loud",
    "omg": "oh my god",
    "tbh": "to be honest",
    "asap": "as soon as possible",
    "ty": "thank you",
    "thx": "thanks"
}

while True:
    data, address = server_socket.recvfrom(1024)

    message = data.decode()

    print("\nMessage received:", message)

    words = message.split()
    translated = []

    for word in words:
        clean_word = word.lower().strip(".,!?")

        if clean_word in abbreviations:
            translated.append(abbreviations[clean_word])
        else:
            translated.append(word)

    result = " ".join(translated)

    print("Translated message:", result)

    server_socket.sendto(result.encode(), address)