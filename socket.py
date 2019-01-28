import socket

host = "10.0.0.34"
port = 80

sock = socket.socket()

sock.connect((host, port))

message = "bi love ryan reynolds"
data = "b"
sock.send(message)

while len(data) < len(message):
  data += sock.recv(1)

print(data)

sock.close()


