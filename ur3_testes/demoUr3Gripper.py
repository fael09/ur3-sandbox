#!/usr/bin/env python

import socket
import time

# Socket Config
HOST = "192.168.1.56" # The remote host
PORT = 30002          # The same port as used by the server
BUFFER_SIZE = 100000
# Start Socket Communication with robot
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))


# Send it to robot through socket

s.send ("movej([0, -1.57, 0.0, -1.57, 0.0, 3.14], a=1.0, v=0.5)" + "\n")
#s.send ("RG2(5,40,0.0,True,False,False)"+"\n")
data = s.recv(BUFFER_SIZE)

# Close Connection
s.close()

for i in data:
    print hex(ord(i))