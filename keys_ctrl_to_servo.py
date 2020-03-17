#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
from std_msgs.msg import String
from std_msgs.msg import UInt16
import numpy as np
import time
from geometry_msgs.msg import Twist
key_mapping = { '8': [60,60], '2': [100,100], '4': [100,60],'6': [60,100],'5':[0,0] }

#def keys_cb(msg):
def keys_cb(msg, twist_pub):
  if len(msg.data) == 0 or not key_mapping.has_key(msg.data[0]):
    return # unknown key.

  vels = key_mapping[msg.data[0]]
#  mtrs = np.array(mtrs, dtype='UInt16')
  #mtrsR = np.array(mtrsR, dtype='UInt16')
  t = Twist()
  t=UInt16()
  t=vels
#  print(servo_L,servo_L.dtype)
#  print(servo_R,servo_R.dtype)
  twist_pub.publish(t)
#  servo_L = UInt16()
#  servo_R = UInt16()
#  servo_L = mtrs
#  servo_R = mtrs
 # t = mtrs
  publisher.publish(servo_L)
  publisher.publish(servo_R)
  print("L",servo_L)
  print("R",servo_R)



if __name__ == '__main__':
  #keys_to_servoノード作成
  rospy.init_node('keys_ctrl_to_servo')
  #servoトピックにUInt16型のメッセージを送る
  publisher = rospy.Publisher('servo_L', UInt16, queue_size=1)
  time.sleep(0.1)
  publisher = rospy.Publisher('servo_R', UInt16, queue_size=1)
  rospy.Subscriber('keys', String, keys_cb, publisher)
  rospy.spin()
