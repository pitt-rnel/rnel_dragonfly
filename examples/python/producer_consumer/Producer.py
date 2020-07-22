#!/usr/bin/python
import time
import PyDragonfly
from PyDragonfly import copy_to_msg
import message_defs as md
import sys

MID_PRODUCER = 10

if __name__ == "__main__":
    mod = PyDragonfly.Dragonfly_Module(MID_PRODUCER, 0)
    mod.ConnectToMMM("localhost:7111")
    
    print("Producer running")

    a = 0
    run = True
    while run:
        out_msg = PyDragonfly.CMessage(md.MT_TEST_DATA)

        data = md.MDF_TEST_DATA()
        data.a = a
        data.b = -3
        data.x = 1.234
        copy_to_msg(data, out_msg)
        mod.SendMessage(out_msg)

        print("Sent message ", out_msg.GetHeader().msg_type)
        print("  Data = [a: %d, b: %d, x: %f]" % (data.a, data.b, data.x))
        
        a += 1
        
        time.sleep(1)
