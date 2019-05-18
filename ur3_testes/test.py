  def RG2(target_width=110, target_force=40, payload=0.0, set_payload=False, depth_compensation=False, slave=False):
  	grip_detected=False
  	if slave:
  		slave_grip_detected=False
  	else:
  		master_grip_detected=False
  	end
  	timeout = 0
  	timeout_limit = 750000
  	while get_digital_in(9) == False:
  	  if timeout > timeout_limit:
  	    break
  	  end
  	  timeout = timeout+1
  	  sync()
  	end
  	def bit(input):
  	  msb=65536
  	  local i=0
  	  local output=0
  	  while i<17:
  	    set_digital_out(8,True)
  	    if input>=msb:
  	      input=input-msb
  	      set_digital_out(9,False)
  	    else:
  	      set_digital_out(9,True)
  	    end
  	    if get_digital_in(8):
  	      out=1
  	    end
  	    sync()
  	    set_digital_out(8,False)
  	    sync()
  	    input=input*2
  	    output=output*2
  	    i=i+1
  	  end
  	  return output
  	end
  	target_width=target_width+9.2
  	if target_force>40:
  	target_force=40
  	end
  	if target_force<4:
  	target_force=4
  	end
  	if target_width>110:
  	target_width=110
  	end
  	if target_width<0:
  	target_width=0
  	end
  	rg_data=floor(target_width)*4
  	rg_data=rg_data+floor(target_force/2)*4*111
  	rg_data=rg_data+32768
  	if slave:
  	rg_data=rg_data+16384
  	end
  	bit(rg_data)  # aqui acaba o rastro da varável target_width
  	if depth_compensation:
  	finger_length = 55.0/1000
  	finger_heigth_disp = 5.0/1000
  	center_displacement = 7.5/1000
  
  	start_pose = get_forward_kin()
  	set_analog_inputrange(2, 1)
  	zscale = (get_analog_in(2)-0.026)/2.9760034
  	zangle = zscale*1.57079633+-0.08726646
  	zwidth = 5.0+110*sin(zangle)
  
  	start_depth = cos(zangle)*finger_length
  
  	sleep(0.016)
  	timeout = 0
  	while get_digital_in(9) == True:
  	  timeout=timeout+1
  	  sleep(0.008)
  	  if timeout > 20:
  	    break
  	  end
  	end
  	timeout = 0
  	timeout_limit = 750000
  	while get_digital_in(9) == False:
  	  zscale = (get_analog_in(2)-0.026)/2.9760034
  	  zangle = zscale*1.57079633+-0.08726646
  	  zwidth = 5.0+110*sin(zangle)
  	  measure_depth = cos(zangle)*finger_length
  	  compensation_depth = (measure_depth - start_depth)
  	  target_pose = pose_trans(start_pose,p[0,0,-compensation_depth,0,0,0])
  	  if timeout > timeout_limit:
  	    break
  	  end
  	  timeout=timeout+1

  	servoj(get_inverse_kin(target_pose),0,0,0.008,0.01,2000)
  	if point_dist(target_pose, get_forward_kin()) > 0.005:
  	popup("Lower grasping force or max width",title="RG-lag threshold exceeded", warning=False, error=False, blocking=False)
  	end
  	end
  	nspeed = norm(get_actual_tcp_speed())
  	while nspeed > 0.001:
  	servoj(get_inverse_kin(target_pose),0,0,0.008,0.01,2000)
  	nspeed = norm(get_actual_tcp_speed())
  	end
  	stopj(2)
  	end
  	if depth_compensation==False:
  	timeout = 0
  	timeout_count=20*0.008/0.008
  	while get_digital_in(9) == True:
  	  timeout = timeout+1
  	  sync()
  	  if timeout > timeout_count:
  	    break
  	  end
  	end
  	timeout = 0
  	timeout_limit = 750000
  	while get_digital_in(9) == False:
  	  timeout = timeout+1
  	  sync()
  	  if timeout > timeout_limit:
  	    break
  	  end
  	end
  	end
  	sleep(0.024)
  	if set_payload:
  	if slave:
  	if get_analog_in(3) < 2:
  	zslam=0
  	else:
  	zslam=payload
  	end
  	else:
  	if get_digital_in(8) == False:
  	zmasm=0
  	else:
  	zmasm=payload
  	end
  	end
  	zload=zmasm+zslam+zsysm
  	set_payload(zload,[(zsysx*zsysm+zmasx*zmasm+zslax*zslam)/zload,(zsysy*zsysm+zmasy*zmasm+zslay*zslam)/zload,(zsysz*zsysm+zmasz*zmasm+zslaz*zslam)/zload])
  	end
  	master_grip_detected=False
  	master_lost_grip=False
  	slave_grip_detected=False
  	slave_lost_grip=False
  	if True == get_digital_in(8):
  		master_grip_detected=True
  	end
  	if get_analog_in(3)>2:
  		slave_grip_detected=True
  	end
  	grip_detected=False
  	lost_grip=False
  	if True == get_digital_in(8):
  		grip_detected=True
  	end
  	zscale = (get_analog_in(2)-0.026)/2.9760034
  	zangle = zscale*1.57079633+-0.08726646
  	zwidth = 5.0+110*sin(zangle)
  	global measure_width = (floor(zwidth*10))/10-9.2
  	if slave:
  	slave_measure_width=measure_width
  	else:
  	master_measure_width=measure_width
  	end
  	return grip_detected
  end