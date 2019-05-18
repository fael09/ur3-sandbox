#!/usr/bin/env python

# Echo client program
import socket
import time
HOST = "192.168.1.56" # The remote host
PORT = 30002          # The same port as used by the server

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))


s.send("set_digital_out(1,True)" + "\n") # 
time.sleep(0.1)
s.send("set_digital_out(8,True)" + "\n") # 
time.sleep(2)

#time.sleep(2)
s.send("RG2(target_width=70, target_force=40, payload=0.0, set_payload=False, depth_compensation=False, slave=False)" + "\n")
time.sleep(10)


data = s.recv(1024)

s.close()

print("Received ", repr(data))
