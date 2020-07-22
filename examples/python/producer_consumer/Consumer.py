#!/usr/bin/python
import sys
import time

from pydragonfly import DragonflyModule
import message_defs as md


MID_CONSUMER = 11


if __name__ == '__main__':
    mod = DragonflyModule(MID_CONSUMER, 0)
    mod.connect(mm_ip='localhost:7111')
    mod.subscribe(md.MT_TEST_DATA)
    
    print('Consumer running...')
    
    while (1):
        # Blocking read.
        # Use timeout parameter in method if you want to timeout.
        # Check if cmsg is None if using a timeout
        cmsg = mod.read_message(timeout=-1)

        # For demonstration. cmsg should never be None if read_message is blocking
        if cmsg:
            print('Received message ', cmsg.get_header().msg_type)

            if cmsg.get_header().msg_type == md.MT_TEST_DATA:
                msg = cmsg.to_msg_def(msg_def_type=md.MDF_TEST_DATA)
                print('    Data = [a: %d, b: %d, x: %f]' % (msg.a, msg.b, msg.x))
        
    # DragonflyModule disconnects automatically when destroyed
