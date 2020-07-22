#!/usr/bin/python
import sys
import time

from pydragonfly import DragonflyModule, MT_EXIT
import message_defs as md


MID_REQUEST = 11


# Note: Request must be started second

if __name__ == '__main__':
    mod = DragonflyModule(MID_REQUEST, 0)
    mod.connect(mm_ip='localhost:7111')
    mod.subscribe(md.MT_TEST_DATA)
    mod.subscribe(MT_EXIT)
    
    print('Request running...')

    while True:
        mod.send_signal(msg_type=md.MT_REQUEST_TEST_DATA)
        print('Sent request for data')

        # Blocking read
        cmsg = mod.read_message()
        print('Received message', cmsg.get_header().msg_type)

        if cmsg.get_header().msg_type == md.MT_TEST_DATA:
            msg = cmsg.to_msg_def(md.MDF_TEST_DATA)
            print('    Data = [a: %d, b: %d, x: %f]' % (msg.a, msg.b, msg.x))
            time.sleep(1)
