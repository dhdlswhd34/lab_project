#ifndef __MSOCKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MSOCKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <cCommon.h>
#include <mtifSocket.h>

#define MAX_BUF_SZ            1024
#define SOCKET_BUF_SFT        10
typedef struct
{
	int fd;
	unsigned int ip;
	unsigned short port;
	unsigned char b[1024];
}mtifSocketPackInfo;

typedef struct
{
	mtifSocketPackInfo info[FD_SETSIZE];
}mtifSocketPack;

typedef struct
{
  int   a[4];
} fdsetex;

typedef struct
{
  fdsetex*       fds;
  xREG        REG;
  unsigned char  mode;
  //unsigned char pbuf[32];
  int fd;
  XMTIFSocket    m;
	mtifSocketPack pack;
  void* info;
  void* pif;
}mtifSocket;


void* on_socket_status(void*,int,unsigned char*,int,void*,int,void*);
void* on_socket_read(void*,int,unsigned char*,int,void*,int,void*);
int socket_init(void*,void*,void*,void*);
int socket_release(void*,void*,void*,void*);
int socket_open(void*,void*,void*,void*);
int socket_close(void*,void*,void*,void*);
int socket_write(void*,void*,void*,void*);
int socket_status(void*,void*,void*,void*);

#endif
