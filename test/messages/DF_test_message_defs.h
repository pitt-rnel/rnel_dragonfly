/*
 * messages ids
 */
// message request 1: just a signal, no fields
// provider will send back predefined values
#define MT_REQUEST_TEST_1 101
// message request 2: message with fields
// values send will be copied in reply
#define MT_REQUEST_TEST_2 102
// reply message
#define MT_REPLY_TEST 103

/*
 * messages definition
 */
// message request 2 structure
typedef struct
{
  char  tss[32];
  char  string1[64];
  char  string2[128];
  int   number1;
  float number2;
} MDF_REQUEST_TEST_2;
// message reply structure
typedef struct
{
  char  tss[32];
  char  tsr[32];
  char  string1[64];
  char  string2[128];
  int   number1;
  float number2;
} MDF_REPLY_TEST;



