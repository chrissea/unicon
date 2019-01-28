import socket

host = "192.168.1.78"
port = 80

sock = socket.socket()

sock.connect((host, port))

message = "hello world"
sock.send(message)

while len(data) < len(message):
  data += sock.recv(1)

print(data)

sock.close()


