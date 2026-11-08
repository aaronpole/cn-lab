import socket, json

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(("0.0.0.0",12345))
s.listen(1)
print("Server Listening...")
c, _ = s.accept()

with c:
    f = c.makefile("rwb")
    d = json.loads(f.readline().decode())
    N,m = d["N"],d["mat"]

    up = all(m[i][j] == 0 for i in range(N) for j in range(N) if i > j)
    low = all(m[i][j] == 0 for i in range(N) for j in range(N) if i < j)
    diag = all(m[i][j] == 0 for i in range(N) for j in range(N) if i != j)

    res = "Diagonal" if diag else "Upper Triangular" if up else "Lower Triangular" if low else "Non Special"

    f.write((res+"\n").encode())
    f.flush()
    print("Sent back to client")
s.close()