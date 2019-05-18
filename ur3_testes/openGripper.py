#!/usr/bin/env python

import socket
import time

# Socket Config
HOST = "192.168.1.56" # The remote host
PORT = 30002          # The same port as used by the server
BUFFER_SIZE = 1024
# Start Socket Communication with robot
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

# Read my ur3script program file
file = open("treste1.script","r")
myProgram = file.read()

# Send it to robot through socket
s.send(myProgram)
data = s.recv(BUFFER_SIZE)
# Close Connection
s.close()
print "received data:", data