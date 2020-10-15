#!/usr/bin/python
import time

import pydragonfly as df
import message_defs as md


MID_REQUEST = 11


# Note: Request must be started second

if __name__ == '__main__':
    mod = df.Dragonfly_Module(MID_REQUEST, 0)
    
    # Connect to message manager running on local machine
    mod.ConnectToMMM('localhost:7111')

    # Subscribe to TEST_DATA message types
    mod.Subscribe(md.MT_TEST_DATA)

    # Subscribe to special Dragonfly message types
    mod.Subscribe(df.MT_KILL)
    mod.Subscribe(df.MT_EXIT)
    
    print('Request running...')

    run = True

    while run:
        # Send a signal to get data
        mod.SendSignal(md.MT_REQUEST_TEST_DATA)
        print('Sent request for data')

        # Blocking read.
        # Use timeout parameter in method if you want to timeout (default is blocking).
        msg = df.CMessage()
        mod.ReadMessage(msg)

        print('Received message ', msg.GetHeader().msg_type)

        # Always check the message type, even if subscribed to one message type
        if msg.GetHeader().msg_type == md.MT_TEST_DATA:
            msg_data = md.MDF_TEST_DATA()
            df.copy_from_msg(msg_data, msg)
            print('    Data = [a: %d, b: %d, x: %f]' % (msg_data.a, msg_data.b, msg_data.x))

        # Check for special Dragonfly message types
        elif msg.GetHeader().msg_type in (df.MT_EXIT, df.MT_KILL):
            print('Stopping Request')
            run = False

    mod.DisconnectFromMMM()