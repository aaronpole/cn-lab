
import socket
import json
import random

HOST = "127.0.0.1"
PORT = 12345

# Input matrix order
N = int(input("Enter order of matrix (N): "))

if not 1 <= N <= 10:
    raise ValueError("Enter N between 1 and 10")

# Generate random matrix
matrix = []

for i in range(N):
    row = []
    for j in range(N):
        row.append(random.randint(0, 50))
    matrix.append(row)

# Display matrix
print("\nGenerated Matrix:")
for row in matrix:
    print(row)

# Create TCP socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to server
client.connect((HOST, PORT))

# Prepare data
request = {
    "N": N,
    "matrix": matrix
}

# Send matrix to server
file = client.makefile("rwb")

file.write((json.dumps(request) + "\n").encode())
file.flush()

# Receive result
result = file.readline().decode().strip()

print("\nMatrix Type:", result)

# Close socket
file.close()
client.close()
