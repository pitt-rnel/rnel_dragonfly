// This is the SWIG interface file for generating structures that will enable
// one to use the Dragonfly application classes/interface from Python.
// Andrew S. Whitford (asw35) 01/09, 06/09, 09/09
// Angus McMorland
// Emrah Diril 05/01/2013

%define DOCSTRING
"Python interface to the University of Pittsburgh Motor Control Lab's Dragonfly messaging system."
%enddef

%module(docstring=DOCSTRING) pydragonfly
%feature("autodoc", "1");

%rename(msg_type) MessageType;

// Rename Dragonfly_Module and methods to more pythonic syntax
%rename(DragonflyModule) Dragonfly_Module;
%rename(cleanup) Cleanup;
%rename(init_variables) InitVariables;
%rename(connect) ConnectToMMM;
%rename(disconnect) DisconnectFromMMM;
%rename(is_connected) IsConnected;
%rename(send_module_ready) SendModuleReady;
%rename(subscribe) Subscribe;
%rename(unsubscribe) Unsubscribe;
%rename(pause_subscription) PauseSubscription;
%rename(resume_subscription) ResumeSubscription;
%rename(send_message) SendMessage;
%rename(send_message_df) SendMessageDF;
%rename(send_signal) SendSignal;
%rename(send_self_signal) SendSelfSignal;
%rename(read_message) ReadMessage;
%rename(wait_for_signal) WaitForSignal;
%rename(wait_for_message) WaitForMessage;
%rename(set_timer) SetTimer;
%rename(cancel_timer) CancelTimer;
%rename(self_notify_expired_timer) SelfNotifyExpiredTimer;
%rename(up_time) UpTime;
%rename(get_pid) GetPid;
%rename(get_message_count) GetMessageCount;
%rename(get_host_id) GetHostID;
%rename(get_module_id) GetModuleID;

%rename(get_header) GetHeader;

%feature("shadow") Dragonfly_Module::ConnectToMMM %{
def connect(self, mm_ip='localhost:7111', logger_status=0, read_dd_file=0, daemon_status=0):
    args = (mm_ip, logger_status, read_dd_file, daemon_status)
    return _pydragonfly.DragonflyModule_connect(self, *args)
%}

%feature("shadow") Dragonfly_Module::SendMessage %{
def send_message(self, msg_def, msg_type, dest_mod_id=0, dest_host_id=0):
    out_msg = CMessage(msg_type)
    copy_to_msg(msg_def, out_msg)
    return _pydragonfly.DragonflyModule_send_message(self, out_msg, dest_mod_id, dest_host_id)
%}

%feature("shadow") Dragonfly_Module::ReadMessage %{
def read_message(self, timeout=-1):
    in_msg = CMessage()
    count = _pydragonfly.DragonflyModule_read_message(self, in_msg, timeout)
    if count > 0:
        return in_msg
    else:
        return None
%}

%{
#include "MyCString.h"
#include "Dragonfly.h"
%}

%exception {
	try {
		$action
	}
	catch (MyCException e) {
	    MyCString errMsg;
		
		e.AppendTraceToString(errMsg);
		PyErr_SetString(PyExc_Exception, errMsg.GetContent());
		return NULL;
	}
}

%inline %{
	void *void_ptr(long long n)
	{
		return (void *) n;
	}
%}

%pythoncode %{
from ctypes import memmove, addressof, sizeof

def copy_from_msg(data, cmsg):
    cmsg.GetData(void_ptr(addressof(data)))

def copy_to_msg(data, cmsg):
	cmsg.SetData(void_ptr(addressof(data)), sizeof(data))

def read_msg_data(data, cmsg):
    cmsg.GetData(void_ptr(addressof(data)))
	
import warnings
import functools

def deprecated(reason):
    """
    This is a decorator which can be used to mark functions
    as deprecated. It will result in a warning being emitted
    when the function is used.
    """
    def decorator(func1):
        @functools.wraps(func1)
        def wrapper_func(*args, **kwargs):
            warnings.simplefilter('always', DeprecationWarning)
            warnings.warn(
                reason,
                category=DeprecationWarning,
                stacklevel=2)
            warnings.simplefilter('default', DeprecationWarning)
            return func1(*args, **kwargs)
        return wrapper_func
    return decorator

%}

%include "Dragonfly.h"

%include "Dragonfly_types.h"

// Helper classes for working with subscription lists and variable-length data
// types.
//%include "carrays.i"
//%array_class(int, MSG_TYPE_ARRAY)
//%array_class(double, DoubleArray)

%pythoncode %{
def to_msg_def(self, msg_def_type):
    msg_data = msg_def_type()
    copy_from_msg(msg_data, self)
    return msg_data

CMessage.to_msg_def = to_msg_def

def read_to_cmsg(self, cmsg, timeout=-1):
    return _pydragonfly.DragonflyModule_read_message(self, cmsg, timeout)

DragonflyModule.read_to_cmsg = read_to_cmsg

def send_cmsg(self, cmsg, dest_mod_id=0, dest_host_id=0):
    return _pydragonfly.DragonflyModule_send_message(self, cmsg, dest_mod_id, dest_host_id)

DragonflyModule.send_cmsg = send_cmsg

def __del__(self):
    if self.is_connected:
        self.disconnect()

DragonflyModule.__del__ = __del__

%}


// Backwards compatibility

%pythoncode %{

def GetHeader(self):
    return self.get_header()

CMessage.GetHeader = GetHeader

@deprecated('Dragonfly_Module is deprecated. Please use pydragonfly.DragonflyModule')
class Dragonfly_Module(DragonflyModule):

    def Cleanup(self):
        return _pydragonfly.DragonflyModule_cleanup(self)

    def InitVariables(self, ModuleID, HostID, use_time_card=0):
        return _pydragonfly.DragonflyModule_init_variables(self, ModuleID, HostID, use_time_card)

    def ConnectToMMM(self, *args):
        return _pydragonfly.DragonflyModule_connect(self, *args)

    def DisconnectFromMMM(self):
        return _pydragonfly.DragonflyModule_disconnect(self)
    
    def IsConnected(self):
        return _pydragonfly.DragonflyModule_is_connected(self)

    def SendModuleReady(self):
        return _pydragonfly.DragonflyModule_send_module_ready(self)

    def Subscribe(self, MessageType):
        return _pydragonfly.DragonflyModule_subscribe(self, MessageType)

    def Unsubscribe(self, msg_type):
        return _pydragonfly.DragonflyModule_unsubscribe(self, msg_type)

    def PauseSubscription(self, msg_type):
        return _pydragonfly.DragonflyModule_pause_subscription(self, msg_type)

    def ResumeSubscription(self, msg_type):
        return _pydragonfly.DragonflyModule_resume_subscription(self, msg_type)

    def SendMessage(self, msg, dest_mod_id=0, dest_host_id=0):
        return _pydragonfly.DragonflyModule_send_message(self, msg, dest_mod_id, dest_host_id)

    def SendMessageDF(self, M, dest_mod_id=0, dest_host_id=0):
        return _pydragonfly.DragonflyModule_send_message_df(self, M, dest_mod_id, dest_host_id)

    def SendSignal(self, MessageType, dest_mod_id=0, dest_host_id=0):
        return _pydragonfly.DragonflyModule_send_signal(self, MessageType, dest_mod_id, dest_host_id)

    def SendSelfSignal(self, msg_type):
        return _pydragonfly.DragonflyModule_send_self_signal(self, msg_type)

    def ReadMessage(self, msg, timeout=-1):
        return _pydragonfly.DragonflyModule_read_message(self, msg, timeout)

    def WaitForSignal(self, SigType, blocking=1):
        return _pydragonfly.DragonflyModule_wait_for_signal(self, SigType, blocking)

    def WaitForMessage(self, M, MsgType=-1):
        return _pydragonfly.DragonflyModule_wait_for_message(self, M, MsgType)

    def SetTimer(self, time_ms):
        return _pydragonfly.DragonflyModule_set_timer(self, time_ms)

    def CancelTimer(self, timer_id):
        return _pydragonfly.DragonflyModule_cancel_timer(self, timer_id)

    def SelfNotifyExpiredTimer(self, timer_id):
        return _pydragonfly.DragonflyModule_self_notify_expired_timer(self, timer_id)

    def UpTime(self):
        return _pydragonfly.DragonflyModule_up_time(self)

    def GetPid(self):
        return _pydragonfly.DragonflyModule_get_pid(self)

    def GetMessageCount(self):
        return _pydragonfly.DragonflyModule_get_message_count(self)

    def GetHostID(self):
        return _pydragonfly.DragonflyModule_get_host_id(self)

    def GetModuleID(self):
        return _pydragonfly.DragonflyModule_get_module_id(self)

%}