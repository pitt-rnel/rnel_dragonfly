
/**************************************************************************
 *
 *  $Id: mbgdevio_import.c 1.1 2015/11/06 15:28:12Z martin REL_M $
 *
 *  Copyright (c) Meinberg Funkuhren, Bad Pyrmont, Germany
 *
 *  Description:
 *    Import mbgdevio API functions dynamically at runtime.
 *    This removes dependencies on the availability of the
 *    mbgdevio DLL. 
 *
 * -----------------------------------------------------------------------
 *  $Log: mbgdevio_import.c $
 *  Revision 1.1  2015/11/06 15:28:12Z  martin
 *  Initial revision.
 *
 **************************************************************************/

#define _MBGDEVIO_IMPORT
  #include <mbgdevio_import.h>
#undef _MBGDEVIO_IMPORT


static const char *mbgdevio_dll_name = "mbgdevio.dll";
static HINSTANCE mbgdevio_dll_handle;



// The STRINGIFY() macro can be used to convert a macro argument
// to a string. The XSTRINGIFY() macro is simply a helper macro
// which should not be used alone.
#define STRINGIFY(x) XSTRINGIFY(x)
#define XSTRINGIFY(x) #x


#define _import_mbgdevio_fnc_chk( _f )                       \
{                                                            \
  fnc_##_f = (fnc_##_f##_t *)                                \
    GetProcAddress( mbgdevio_dll_handle, STRINGIFY( _f ) );  \
                                                             \
  if ( fnc_##_f == NULL )                                    \
    if ( rc == ERROR_SUCCESS )                               \
      rc = GetLastError();                                   \
}


#define _unimport_mbgdevio_fnc( _f ) \
  fnc_##_f = NULL;




static /*HDR*/
DWORD mbg_svc_load_dll( const char *dll_name, HINSTANCE *ph )
{
  if ( *ph == NULL )
  {
    // Try to load the DLL.
    *ph = LoadLibrary( dll_name );

    // If unsuccessfull, we can't go on.
    if ( *ph == NULL )
      return GetLastError();
  }

  return ERROR_SUCCESS;

}  // mbg_svc_load_dll



static /*HDR*/
void mbg_unimport_mbgdevio_api( void )
{
  if ( mbgdevio_dll_handle )
  {
    // Be sure to import the same list of functions
    // in mbg_import_mbgdevio_api.
    //_unimport_mbgdevio_fnc( mbg_get_time );
    //_unimport_mbgdevio_fnc( mbg_get_hr_time );
	_unimport_mbgdevio_fnc( mbg_find_devices );
	_unimport_mbgdevio_fnc( mbg_open_device );
	_unimport_mbgdevio_fnc( mbg_xhrt_poll_thread_create );
	_unimport_mbgdevio_fnc( mbg_get_xhrt_time_as_pcps_hr_time );
	_unimport_mbgdevio_fnc( mbg_xhrt_poll_thread_stop );
	_unimport_mbgdevio_fnc( mbg_close_device );

    FreeLibrary( mbgdevio_dll_handle );
    mbgdevio_dll_handle = NULL;
  }

}  // mbg_unimport_mbgdevio_api



/*HDR*/
DWORD mbg_import_mbgdevio_api( void )
{
  DWORD rc;

  rc = mbg_svc_load_dll( mbgdevio_dll_name, &mbgdevio_dll_handle );

  if ( rc == ERROR_SUCCESS )
  {
    // Be sure to unimport the same list of functions
    // in mbg_unimport_mbgdevio_api.
    //_import_mbgdevio_fnc_chk( mbg_get_time );
    //_import_mbgdevio_fnc_chk( mbg_get_hr_time );
	_import_mbgdevio_fnc_chk( mbg_find_devices );
	_import_mbgdevio_fnc_chk( mbg_open_device );
	_import_mbgdevio_fnc_chk( mbg_xhrt_poll_thread_create );
	_import_mbgdevio_fnc_chk( mbg_get_xhrt_time_as_pcps_hr_time );
	_import_mbgdevio_fnc_chk( mbg_xhrt_poll_thread_stop );
	_import_mbgdevio_fnc_chk( mbg_close_device );
	
  }

  if ( rc != ERROR_SUCCESS )
    mbg_unimport_mbgdevio_api();   // clean up
  else
    atexit( mbg_unimport_mbgdevio_api );

  return rc;

}  // mbg_import_mbgdevio_api



