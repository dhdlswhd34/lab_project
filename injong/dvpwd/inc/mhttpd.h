#ifndef __MHTTPD_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MHTTPD_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <cCommon.h>
#include <mtifHttp.h>

#define MAX_BUF_SZ      4096

typedef struct
{
  xREG            REG;

  int fd;
	char buf[MAX_BUF_SZ];
  char url[MAX_BUF_SZ];
  XMTIFHttp  m;
  void* info;
  void* pif;
} mtifHttpd;


int httpd_status(void*,void*,void*,void*);


#endif
