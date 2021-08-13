#if 1
//#ifndef __MSHM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
//#define __MSHM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <cCommon.h>
#include <mtifSHM.h>

#define MAX_BUF_SZ            32
#define MAX_BUF_QUE           16
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

}mtifSHM_S;


int cxshm_s_init(void*,void*,void*,void*);
int cxshm_s_release(void*,void*,void*,void*);
int cxshm_s_open(void*,void*,void*,void*);
int cxshm_s_close(void*,void*,void*,void*);
int cxshm_s_write(void*,void*,void*,void*);
int cxshm_s_read(void*,void*,void*,void*);
int cxshm_s_status(void*,void*,void*,void*);

#endif
