
import socket
import json

HOST = "0.0.0.0"
PORT = 12345

# Create TCP server socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind socket to IP and port
server.bind((HOST, PORT))

# Listen for client
server.listen(3)

print("Server waiting for client...")

# Accept client connection
conn, addr = server.accept()

print("Connected to:", addr)

# Receive matrix data
file = conn.makefile("rwb")
data = file.readline()

request = json.loads(data.decode())

N = request["N"]
matrix = request["matrix"]

# Identify matrix type
upper = True
lower = True
diagonal = True

for i in range(N):
    for j in range(N):

        if i > j and matrix[i][j] != 0:
            upper = False

        if i < j and matrix[i][j] != 0:
            lower = False

        if i != j and matrix[i][j] != 0:
            diagonal = False

# Determine result
if diagonal:
    result = "Diagonal Matrix"

elif upper:
    result = "Upper Triangular Matrix"

elif lower:
    result = "Lower Triangular Matrix"

else:
    result = "Not a special matrix"

print("Matrix received:")
for row in matrix:
    print(row)

print("Matrix Type:", result)

# Send result to client
file.write((result + "\n").encode())
file.flush()

# Close connection
file.close()
conn.close()
server.close()
