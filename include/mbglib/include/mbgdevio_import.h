
/**************************************************************************
 *
 *  $Id: mbgdevio_import.h 1.1 2015/11/06 15:28:22Z martin REL_M $
 *
 *  Copyright (c) Meinberg Funkuhren, Bad Pyrmont, Germany
 *
 *  Description:
 *    Definitions and prototypes for mbgdevio_import.c.
 *
 *  To avoid dependencies on the availability of a particular DLL at
 *  runtime, an application can dynamically import every function it
 *  needs from that DLL at program start and set up some pointers
 *  to the imported functions, and call the API functions *only*
 *  via those pointers.
 * 
 *  This works well if the DLL is available and all functions could
 *  be imported, but if the DLL is not available, or not all functions
 *  could be imported then some or all function pointers are NULL,
 *  and the application will trap whenever it tries to call such
 *  function via the unassigned pointer.
 * 
 *  This source module provides the mbg_import_mbgdevio_api() function
 *  which returns 0 if all API functions could be imported successfully.
 *  So an application can call this function at startup, and use the
 *  imported functions *only* if the import finished successfully.
 *
 * -----------------------------------------------------------------------
 *  $Log: mbgdevio_import.h $
 *  Revision 1.1  2015/11/06 15:28:22Z  martin
 *  Initial revision.
 *
 **************************************************************************/

#ifndef _MBGDEVIO_IMPORT_H
#define _MBGDEVIO_IMPORT_H


/* Other headers to be included */

#include <mbgdevio.h>


#ifdef _MBGDEVIO_IMPORT
 #define _ext
 #define _DO_INIT
#else
 #define _ext extern
#endif


/* Start of header body */

#ifdef __cplusplus
extern "C" {
#endif

  
// To import API functions dynamically we need a function typedef
// for each function prototype, and a function pointer variable.
// To simplify the source code we use the following naming conventions:
//
// Function name:     mbg_get_time    (original name from mbgdevio.h)
// Function type:     mbg_get_time_t  (according prototype of the original function)
// Function pointer:  mbg_get_time_t *fnc_mbg_get_time  (function pointer variable)
//
// A list of function types which have to match the prototypes
// in mbgdevio.h. These typedefs will probably be moved
// to mbgdevio.h later.

typedef _MBG_API_ATTR int (_MBG_API fnc_mbg_find_devices_t)(void);
typedef _MBG_API_ATTR MBG_DEV_HANDLE(_MBG_API fnc_mbg_open_device_t)(unsigned int device_index);
typedef  _MBG_API_ATTR int (_MBG_API fnc_mbg_xhrt_poll_thread_create_t)(MBG_POLL_THREAD_INFO *p_pti, MBG_DEV_HANDLE dh, MBG_PC_CYCLES_FREQUENCY freq_hz, int sleep_ms);
typedef  _MBG_API_ATTR int (_MBG_API fnc_mbg_get_xhrt_time_as_pcps_hr_time_t)(MBG_XHRT_INFO *p, PCPS_HR_TIME *p_hrt);
typedef  _MBG_API_ATTR int (_MBG_API fnc_mbg_xhrt_poll_thread_stop_t)(MBG_POLL_THREAD_INFO *p_pti);
typedef _MBG_API_ATTR void (_MBG_API fnc_mbg_close_device_t)(MBG_DEV_HANDLE *dev_handle);
//typedef _MBG_API_ATTR int (_MBG_API fnc_mbg_get_time_t)( MBG_DEV_HANDLE dh, PCPS_TIME *p ) ;
//typedef _MBG_API_ATTR int (_MBG_API fnc_mbg_get_hr_time_t)( MBG_DEV_HANDLE dh, PCPS_HR_TIME *p ) ;


// A list of function pointer variables using the function types above.
// For each API function to be imported there must be an appropriate
// function pointer variable.

_ext fnc_mbg_find_devices_t *fnc_mbg_find_devices;
_ext fnc_mbg_open_device_t *fnc_mbg_open_device;
_ext fnc_mbg_xhrt_poll_thread_create_t *fnc_mbg_xhrt_poll_thread_create;
_ext fnc_mbg_get_xhrt_time_as_pcps_hr_time_t *fnc_mbg_get_xhrt_time_as_pcps_hr_time;
_ext fnc_mbg_xhrt_poll_thread_stop_t *fnc_mbg_xhrt_poll_thread_stop;
_ext fnc_mbg_close_device_t *fnc_mbg_close_device;
//_ext fnc_mbg_get_time_t *fnc_mbg_get_time;
//_ext fnc_mbg_get_hr_time_t *fnc_mbg_get_hr_time;


// Whenever new variables are added here the import and unimport
// entries in the functions mbg_import_mbgdevio_api() and
// mbg_unimport_mbgdevio_api() need to be updated accordingly.
// Otherwise the functions will not be imported, thus the function
// pointer will always be NULL, and the application will trap if
// the function is called via the pointer.



/* function prototypes: */

/* ----- function prototypes begin ----- */

/* This section was generated automatically */
/* by MAKEHDR, do not remove the comments. */

 DWORD mbg_import_mbgdevio_api( void ) ;

/* ----- function prototypes end ----- */

#ifdef __cplusplus
}
#endif


/* End of header body */

#undef _ext
#undef _DO_INIT

#endif  /* _MBGDEVIO_IMPORT_H */
