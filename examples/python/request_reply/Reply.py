#!/usr/bin/python
import time
import sys

from pydragonfly import DragonflyModule, MT_KILL, MT_EXIT
import message_defs as md


MID_REPLY = 10


# Note: Reply must be started first

if __name__ == '__main__':
    mod = DragonflyModule(MID_REPLY, 0)
    # default mm_ip=localhost:7111
    mod.connect()
    mod.subscribe(md.MT_REQUEST_TEST_DATA)
    
    print('Reply running...')
    
    counter = 1

    run = True
    while run:

        print('Waiting for message')

        cmsg = mod.read_message(timeout=1)
        # Non-blocking read, cmsg might be None
        if cmsg:
            print('Received message', cmsg.get_header().msg_type)

            if cmsg.get_header().msg_type == md.MT_REQUEST_TEST_DATA:
                msg = md.MDF_TEST_DATA()
                msg.a = counter
                msg.b = 47
                msg.x = 123.456
                mod.send_message(msg_def=msg, msg_type=md.MT_TEST_DATA)
                print('Sent message', md.MT_REQUEST_TEST_DATA)

                counter += 1

            elif cmsg.get_header().msg_type in (MT_EXIT, MT_KILL):
                run = False
