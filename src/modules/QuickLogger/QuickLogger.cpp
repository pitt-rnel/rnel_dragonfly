/*
 *  QuickLogger - Logs Dragonfly messages in an attempt to save data or for debugging
 *
 *  Meel Velliste 10/28/2008
 *  Emrah Diril  05/04/2012
 */
#include "QuickLogger.h"

CQuickLogger QL;

//int main( void)
int main( int argc, char *argv[])
{
  try
    {
      //std::cout << "[main] QuickLogger started..." << std::endl;

      char *options;
      char empty_str[] = "";
      #ifdef _UNIX_C
        options = (argc > 1) ? argv[1] : empty_str;
      #else
        options = (argc > 1) ? argv[1] : empty_str;
        //options = (char*) lpCmdLine;
      #endif

      // Run the module
      QL.MainFunction(options);
    }
    catch(MyCException &E)
    {
      MyCString err("QuickLogger: main():");
      E.AppendTraceToString( err);
      std::cout << err;
      return -1;
    }
  return 0;
}

CQuickLogger::CQuickLogger()
{
  TRY {
    // Pre-allocate buffer space for storing messages
    _MessageBufrr.PreallocateBuffer( QL_NUM_PREALLOC_MESSAGES, sizeof( DF_MSG_HEADER), QL_NUM_PREALLOC_DATABYTES);
    _logging = true; // By default, start logging immediately
  } CATCH_and_THROW( "CQuickLogger::CQuickLogger()");
}

CQuickLogger::~CQuickLogger()
{
  TRY {
  } CATCH_and_THROW( "CQuickLogger::~CQuickLogger()");
}

void CQuickLogger::MainFunction( char *cmd_line_options)
{
  TRY {
    CMessage M;
    MDF_SAVE_MESSAGE_LOG FilenameData;
    char Filename[MAX_LOGGER_FILENAME_LENGTH+1];
    time_t ltime;
    struct tm *tm;

    // Get connected
    int logger_status = 1;
    InitVariables( MID_QUICKLOGGER, 0);

    //ConnectToMMM( logger_status);
    if (strlen( cmd_line_options) > 0) {
      char *mm_ip = cmd_line_options;
      ConnectToMMM( mm_ip, logger_status);
    } else {
      ConnectToMMM( logger_status);
    }

    Subscribe( ALL_MESSAGE_TYPES);
    if( SetMyPriority(NORMAL_PRIORITY_CLASS) == 0) 
      throw MyCException( "SetMyPriority failed");
    SendSignal( MT_LM_READY);
    
    printf("QuickLogger connected\n\n");
  
    // Do logging
    try
    {
      // broadcast quicklogger status
      Status( (MyCString) "Pre-allocated space for " + _MessageBufrr.GetNumPreallocMessages() + " messages");
      Status( (MyCString) "Pre-allocated space for " + _MessageBufrr.GetNumPreallocDataBytes() + " data bytes");
       _logging = true; // Start logging immediately by default
      while( 1) {
        ReadMessage( &M);
        //Status( (MyCString) "Received Message (msg_type = " + M.msg_type + ")");
        // save message in buffer
        bool saved = _MessageBufrr.SaveMessage( &M);
        if( !saved) {
          // message not saved because buffer was full
          // get current time
          Status( (MyCString) "\nMessage buffer full, dumping to file");
          AutoDumpBuffer();
          _MessageBufrr.ClearBuffer( );
          Status( "Log saved, message buffer has been reset");
          // Save the message again to the now cleared buffer
          _MessageBufrr.SaveMessage( &M);
        }
        // respond accordingly to the message received
        switch( M.msg_type) {
          case MT_SAVE_MESSAGE_LOG:
            printf("\n");
            Status( "Saving buffer to file" );
            M.GetData( &FilenameData);
            FilenameData.pathname[FilenameData.pathname_length] = 0; // Make sure string is zero-terminated
            DumpBuffer(FilenameData.pathname);
            SendSignal( MT_MESSAGE_LOG_SAVED);
            _MessageBufrr.ClearBuffer( );
            break;
          case MT_PAUSE_MESSAGE_LOGGING:
            printf("\n");
            Status( "Logging paused!");
            _logging = false;
            break;
          case MT_RESUME_MESSAGE_LOGGING:
            printf("\n");
            Status( "Logging resumed!");
            _logging = true;
            break;
          case MT_RESET_MESSAGE_LOG:
            printf("\n");
            Status( "Resetting the message log");
            _MessageBufrr.ClearBuffer( );
            break;
          case MT_DUMP_MESSAGE_LOG:
            printf("\n");
            Status( "Dumping message log");
//            _MessageBufrr.SaveDatafile( "QuickLoggerDump.bin");
            AutoDumpBuffer();
            break;
          case MT_LM_EXIT:
            printf("\n");
            Status( "Auto dumping and Exiting");
            AutoDumpBuffer();
            return;
          default:
            //printf("Ignoring message %d\n", M.msg_type);
            break;
        }
      }
    }
    catch(MyCException &E)
    {
      _MessageBufrr.SaveDatafile( "QuickLoggerDump.bin");
      E.AddToStack("Caught MyCException, saving message log to QuickLoggerDump.bin");
      throw E;
    }
    catch(...)
    {
      _MessageBufrr.SaveDatafile( "QuickLoggerDump.bin");
      throw MyCException( "Caught unknown exception, saving message log to QuickLoggerDump.bin");
    }
  } CATCH_and_THROW( "void CQuickLogger::MainFunction()");
}

void CQuickLogger::Status(const MyCString& msg)
{
  TRY {
    std::cout << msg.GetContent() << std::endl;
    CMessage S( MT_DEBUG_TEXT, msg.GetContent(), msg.GetLen());
    SendMessage( &S);
  } CATCH_and_THROW( "void CQuickLogger::Status(const MyCString& msg)");
}

void CQuickLogger::DumpBuffer( char *Filename)
{
  TRY {
    time_t ltime;
    struct tm *tm;
    // output timestamp right before it start saving the data in the buffer
    ltime = time(NULL);
    tm = localtime(&ltime);
    printf("Dumping buffer to %s\n",Filename);
    printf("Starting Buffer Dump (%d-%d-%d %d:%d:%d)\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    _MessageBufrr.SaveDatafile( Filename );
    printf("Buffer Dump Done (%d-%d-%d %d:%d:%d)\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    Status( (MyCString) "Saved Data to '" + Filename + "':");
    Status( (MyCString) "    Num messages: " + _MessageBufrr.GetNumMessages());
    Status( (MyCString) "    Num data bytes: " + _MessageBufrr.GetNumDataBytes());
  } CATCH_and_THROW( "void DumpBuffer( char Filename[MAX_LOGGER_FILENAME_LENGTH+1])")
}

void CQuickLogger::AutoDumpBuffer()
{
  TRY {
    char Filename[MAX_LOGGER_FILENAME_LENGTH+1];
    time_t ltime;
    struct tm *tm;

    // get current time
    ltime=time(NULL);
    tm=localtime(&ltime);

    // define dump file name : QuickLogger.Dump.<ts>,bin
    sprintf( \
      Filename, \
      "QuickLogger.Dump.%04d%02d%02d%02d%02d%02d.bin", \
      tm->tm_year+1900, \
      tm->tm_mon+1, \
      tm->tm_mday, \
      tm->tm_hour, \
      tm->tm_min, \
      tm->tm_sec);
    printf("Auto Dumping Buffer to %s\n", Filename );
    DumpBuffer(Filename);
  } CATCH_and_THROW( "void AutoDumpBuffer()")
}
