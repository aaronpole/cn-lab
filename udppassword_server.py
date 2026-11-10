import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("127.0.0.1", 5000))
print("Password Server Started")

while True:
    data, addr = s.recvfrom(1024)
    p = data.decode()
    strong = (len(p) >= 8 and
              any(c.isupper() for c in p) and
              any(c.islower() for c in p) and
              any(c.isdigit() for c in p))
    result = "Strong Password" if strong else "Weak Password"
    s.sendto(result.encode(), addr)
