import socket
import sys
#import keyboard

host = "10.0.0.108"
port = 8000

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('# Socket created')

try:
  sock.bind((host, port))
except socket.error as msg:
  print("# bind failed")
  sys.exit()

print("# Socket bind complete")

sock.listen(10)
conn, addr = sock.accept()
print("# connected")

# c-pad
cleft = 0
cright = 0
cup = 0
cdown = 0

# d-pad
dleft = 0
dright = 0
dup = 0
ddown = 0

# buttons
a = 0
b = 0
l = 0
r = 0
z = 0
s = 0

# analog stickf
x = 0
y = 0

while True:
  data = conn.recv(1024)
  if data:
    print repr(data)
    print "end of data"

    for curr in data:
    	when curr == 'n':



#{LEFTheld, RIGHTheld, Aheld, Bheld, Zheld, CUheld, CDheld, CLheld, CRheld};







sock.close()