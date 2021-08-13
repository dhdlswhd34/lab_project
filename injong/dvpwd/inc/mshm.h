#ifndef __MSHM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MSHM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <cCommon.h>
#include <mtifSHM.h>

#define MAX_BUF_SZ            1024
#define MAX_BUF_QUE           512
#define PACKET_BUF_SFT        10

typedef struct
{
  xREG        REG;
  int fd;
	unsigned int   key;
	unsigned int   sz;
  unsigned int   cnt;
	unsigned char* p;
  unsigned char* pp;
  XMTIFSHM       m;
  XMTIFSHM       n;
  void* info;
  void* pif;
  unsigned char buf[MAX_BUF_SZ];
  unsigned char rbuf[MAX_BUF_SZ];

}mtifSHM;


int mshm_init(void*,void*,void*,void*);
int mshm_release(void*,void*,void*,void*);
int mshm_open(void*,void*,void*,void*);
int mshm_close(void*,void*,void*,void*);
int mshm_write(void*,void*,void*,void*);
int mshm_read(void*,void*,void*,void*);
int mshm_status(void*,void*,void*,void*);

#endif
