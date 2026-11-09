import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("127.0.0.1", 5000))

words = {
    "btw": "by the way", "idk": "I do not know",
    "atm": "at the moment", "irl": "in real life",
    "lol": "laughing out loud", "omg": "oh my god",
    "tbh": "to be honest", "asap": "as soon as possible",
    "ty": "thank you", "thx": "thanks"
}

print("UDP Server waiting...")

while True:
    data, addr = s.recvfrom(1024)
    msg = data.decode()
    result = " ".join(words.get(w.lower().strip(".,!?"), w)
                      for w in msg.split())

    print("Translated:", result)
    s.sendto(result.encode(), addr)
