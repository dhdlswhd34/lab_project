#ifndef __MWEBSOCKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MWEBSOCKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <cCommon.h>
#include <mtifWebSocket.h>

#define MAX_FD                1024
#define WS_MAX_BUF_SZ         256
#define WEBSOCKET_BUF_SFT     8


typedef struct
{
	int fd;
	unsigned int ip;
	unsigned short port;
	unsigned char buf[WS_MAX_BUF_SZ];
}mtifWebSocketPackInfo;

typedef struct
{
	mtifWebSocketPackInfo info[MAX_FD];
}mtifWebSocketPack;

typedef struct
{
  int   a[4];  // fd sz  bp  fdp
} wsFDSet;

typedef struct
{
  int   fd;
} wsClientSet;

typedef struct
{
  xREG            REG;

  unsigned char mode;
  unsigned char pbuf[WS_MAX_BUF_SZ];
  unsigned char cbuf[WS_MAX_BUF_SZ];
  unsigned char iobuf[1024];
  int hdrsz;
  int fd;
  XMTIFWebSocket   m;

  wsFDSet*        fds;
  wsClientSet*    cs;

	mtifWebSocketPack pack;
  void* info;
  void* pif;
}mtifWebSocket;


void* on_websocket_status(void*,int,unsigned char*,int,void*,int,void*);
void* on_websocket_read(void*,int,unsigned char*,int,void*,int,void*);
int websocket_init(void*,void*,void*,void*);
int websocket_release(void*,void*,void*,void*);
int websocket_open(void*,void*,void*,void*);
int websocket_close(void*,void*,void*,void*);
int websocket_write(void*,void*,void*,void*);
int websocket_status(void*,void*,void*,void*);

#endif
