#!/usr/bin/python
import sys
import time

from pydragonfly import DragonflyModule
import message_defs as md


MID_PRODUCER = 10


if __name__ == '__main__':
    mod = DragonflyModule(MID_PRODUCER, 0)
    mod.connect(mm_ip='localhost:7111')
    
    print('Producer running')

    a = 0
    run = True
    while run:
        msg = md.MDF_TEST_DATA()
        msg.a = a
        msg.b = -3
        msg.x = 1.234

        mod.send_message(msg_def=msg, msg_type=md.MT_TEST_DATA)

        print('Sent message ', md.MT_TEST_DATA)
        print('    Data = [a: %d, b: %d, x: %f]' % (msg.a, msg.b, msg.x))
        
        a += 1
        
        time.sleep(1)

    # DragonflyModule disconnects automatically when destroyed
