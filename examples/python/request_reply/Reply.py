#!/usr/bin/python
import pydragonfly as df
import message_defs as md


MID_REPLY = 10


# Note: Reply must be started first

if __name__ == '__main__':
    mod = df.Dragonfly_Module(MID_REPLY, 0)
    
    # Connect to message manager running on local machine
    mod.ConnectToMMM('localhost:7111')

    # Subscribe to REQUEST_TEST_DATA message types
    mod.Subscribe(md.MT_REQUEST_TEST_DATA)

    # Subscribe to special Dragonfly message types
    mod.Subscribe(df.MT_EXIT)
    mod.Subscribe(df.MT_KILL)
    
    print('Reply running...')
    
    run = True

    while run:

        print('Waiting for message')

        # Not a blocking call. 1 second specified for the timeout
        in_msg = df.CMessage()
        num_msg = mod.ReadMessage(in_msg, timeout=1.0)

        # Check if we received a message
        if num_msg == 1:
            print('Received message ', in_msg.GetHeader().msg_type)

            # Always check the message type, even if subscribed to one message type
            if in_msg.GetHeader().msg_type == md.MT_REQUEST_TEST_DATA:
                # Create a TEST_DATA reply
                out_msg = df.CMessage(md.MT_TEST_DATA)
                out_data = md.MDF_TEST_DATA()
                out_data.a = -20
                out_data.b = 47
                out_data.x = 123.456

                # Set the message data to message and send
                df.copy_to_msg(out_data, out_msg)
                mod.SendMessage(out_msg)
                print('Sent message ', out_msg.GetHeader().msg_type)

            # Check for special Dragonfly message types
            elif in_msg.GetHeader().msg_type in (df.MT_EXIT, df.MT_KILL):
                print('Stopping Reply')
                run = False

    mod.DisconnectFromMMM()