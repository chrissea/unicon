import socket

host = "10.0.0.34"
port = 80

sock = socket.socket()

sock.connect((host, port))

message = b"Now we Fuck Python"
sock.send(message)

data = b""

while len(data) < len(message):
  data += sock.recv(1)

print(data)

sock.close()




