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

  if (get_digital_out(8) == False) and (get_digital_out(9) == False):
    popup("RG2 has already executed open()", title="Notice",  warning = False, error = False, blocking=True)
  else:
  global grip_detected = False
  enter_critical
    set_digital_out(8, False)
    set_digital_out(9, False)
  exit_critical
  timeout = 0
  while get_digital_in(9) == True:
    timeout = timeout+1
    sync()
    if timeout > 500:
      break
    end
  end

  timeout = 0
  while get_digital_in(9) == False:
    timeout = timeout+1
    sync()
    if timeout > 500:
      popup("RG2 is not responding", title="Error",  warning = False, error=True, blocking=True)
      break
    end
  end
  end
  global grip_detected = False
  global lost_grip = False
  if(True == get_digital_in(8)):
    grip_detected = True
  end
  set_analog_inputrange(2, 1)
  sync()
  sync()
  sync()
    global measure_width = (floor(((get_analog_in(2)-0.026)*110/2.976)*10))/10

s.send("RG2(target_width=70, target_force=40, payload=0.0, set_payload=False, depth_compensation=False, slave=False)" + "\n")
time.sleep(10)



data = s.recv(1024)

s.close()

print("Received ", repr(data))
