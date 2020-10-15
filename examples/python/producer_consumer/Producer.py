#!/usr/bin/python
import time

import pydragonfly as df
import message_defs as md


MID_PRODUCER = 10


if __name__ == '__main__':
    mod = df.Dragonfly_Module(MID_PRODUCER, 0)
    
    # Connect to message manager running on local machine
    mod.ConnectToMMM('localhost:7111')
    
    print('Producer running')

    a = 0
    run = True
    while run:
        out_msg = df.CMessage(md.MT_TEST_DATA)

        data = md.MDF_TEST_DATA()
        data.a = a
        data.b = -3
        data.x = 1.234

        # Set the message data to message and send
        df.copy_to_msg(data, out_msg)
        mod.SendMessage(out_msg)

        print('Sent message ', md.MT_TEST_DATA)
        print('    Data = [a: %d, b: %d, x: %f]' % (data.a, data.b, data.x))
        
        a += 1
        
        time.sleep(1)

    mod.DisconnectFromMMM()
