#ifndef __MSERIAL_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MSERIAL_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <cCommon.h>
#include <mtifSerial.h>

#define NORMAL_MODE           1
#define ASCII_MODE            0
#define HEX_MODE              0

#define MAX_MSERIAL_BUF_COUNT    128
#define MSERIAL_BUF_SZ           2
#define SERIAL_BUF_SFT           0
#define ZIGBEE_INFO_SZ           4

#define STX                0x02
#define ETX                0x03
#define PROTOCOL_SZ        9

typedef struct
{
  xREG        REG;

  unsigned char mode;
  unsigned char idx;
  unsigned char b[MAX_MSERIAL_BUF_COUNT][MSERIAL_BUF_SZ];
  //int bpos;
  unsigned char cb[MAX_MSERIAL_BUF_COUNT];
  int cpos;
  //unsigned char bbuf[MAX_MSERIAL_BUF_COUNT];
  void* fd;
  XMTIFSerial      m;
  void* info;
  void* pif;
  int re_ab;
  int chk;
}mtifSerial;


int serial_status(void*,void*,void*,void*);

#endif
