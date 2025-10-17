// #include "msw.h"
#include <stdbool.h>
#include <stdint.h>

typedef bool BOOL;

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;

typedef unsigned char UCHAR;

#define    NoError                      0
#define    ResultStrCheckError          12
#define    ModuleIdError                17
#define    AdChannelError               18
#define    UnderInputRange              19
#define    ExceedInputRange             20

//WORD /*CALLBACK*/ AnalogIn_87K(DWORD dwBuf[], float fBuf[], char szSend[], char szReceive[]);
WORD /*CALLBACK*/ AnalogInAll_87K(DWORD dwBuf[], float fBuf[], char szSend[], char szReceive[]);
WORD /*CALLBACK*/ AnalogOut_87K(DWORD dwBuf[], float fBuf[], char szSend[], char szReceive[]);
WORD /*CALLBACK*/ DigitalOut_87K(DWORD dwBuf[], float fBuf[], char szSend[], char szReceive[]);