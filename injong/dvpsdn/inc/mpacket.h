#ifndef __MPACKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MPACKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <cCommon.h>
#include <mtifPacket.h>

#define MAX_BUF_SZ            1024
#define MAX_BUF_QUE           512
#define PACKET_BUF_SFT        100
#define bar printf("+-----------------------------------------------------------------+\r\n",*(b))
#define change_bar printf("-----------+\r\n",*(b))

int count_name;


enum header 
{
  MAC_ADRESS_D = 0 , MAC_ADRESS_S, ETHER_TYPE,
  IP_VER, TOS, IP_LENGTH, PACKET_ID, IP_FLAG, TTL, PROTOCAL, IP_H_CHECKSUM, IP_ADRESS_S, IP_ADRESS_D,
  PORT_S, PORT_D, SEQUENCE_NUM, ACKNOW_NUK, FLAG, WINDOW_SZ, TCP_CHECKSUM, URGENT_P, DATA 
};

typedef struct
{
  unsigned char  div_b[MAX_BUF_SZ];
  int* cur;
  char* temp;
  char* name;
  char* sub_name;


}PACKET_HEADER;

typedef struct
{
  xREG        REG;
  int fd;
  unsigned char  b[MAX_BUF_QUE][MAX_BUF_SZ];
  unsigned char  shmp[MAX_BUF_SZ];
  unsigned int   qidx;
  //unsigned int   shmp;
  XMTIFPacket    m;
  void* info;
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
