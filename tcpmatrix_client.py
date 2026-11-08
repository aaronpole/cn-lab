import socket,json,random

N = int(input("Enter order of matrix : "))
m = [[random.randint(0,50) for _ in range(N)] for _ in range(N)]

print("Matrix")
for row in m: print(row)

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect(("127.0.0.1",12345))

f = s.makefile("rwb")
f.write((json.dumps({"N":N,"mat":m}) + "\n").encode())
f.flush()
print("Result : ",f.readline().decode().strip())
f.close()
s.close()