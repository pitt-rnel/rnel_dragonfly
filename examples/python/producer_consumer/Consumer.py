#!/usr/bin/python
import pydragonfly as df
import message_defs as md


MID_CONSUMER = 11


if __name__ == '__main__':
    mod = df.Dragonfly_Module(MID_CONSUMER, 0)
    
    # Connect to message manager running on local machine
    mod.ConnectToMMM('localhost:7111')

    # Subscribe to TEST_DATA message types
    mod.Subscribe(md.MT_TEST_DATA)
    
    print('Consumer running...')
    
    while (1):

        # Blocking read.
        # Use timeout parameter in method if you want to timeout (default is blocking).
        msg = df.CMessage()
        mod.ReadMessage(msg, timeout=-1)

        print('Received message ', msg.GetHeader().msg_type)

        # Always check the message type, even if subscribed to one message type
        if msg.GetHeader().msg_type == md.MT_TEST_DATA:
            # Now we can get the message data
            msg_data = md.MDF_TEST_DATA()
            print('    Data = [a: %d, b: %d, x: %f]' % (msg_data.a, msg_data.b, msg_data.x))
        
    mod.DisconnectFromMMM()
