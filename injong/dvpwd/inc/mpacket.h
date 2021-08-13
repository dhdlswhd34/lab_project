#ifndef __MPACKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MPACKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <cCommon.h>
#include <mtifPacket.h>

#define MAX_BUF_SZ            1024
#define MAX_BUF_QUE           512
#define PACKET_BUF_SFT        10

typedef struct
{
  xREG        REG;
  int fd;
  unsigned char  b[MAX_BUF_QUE][MAX_BUF_SZ];
  unsigned int   qidx;
  unsigned int   rbuf[MAX_BUF_SZ];
  XMTIFPacket    m;
  //XMTIFSHM       k;
  void* info;
  void* pif;
}mtifPacket;


void* on_packet_status(void*,int,unsigned char*,int,void*,int,void*);
void* on_packet_read(void*,int,unsigned char*,int,void*,int,void*);
int packet_init(void*,void*,void*,void*);
int packet_release(void*,void*,void*,void*);
int packet_open(void*,void*,void*,void*);
int packet_close(void*,void*,void*,void*);
int packet_write(void*,void*,void*,void*);
int packet_status(void*,void*,void*,void*);

#endif
