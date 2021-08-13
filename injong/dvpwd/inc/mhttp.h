#ifndef __MHTTP_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MHTTP_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <cCommon.h>
#include <mtifHttp.h>

#define MAX_BUF_SZ      4096

typedef struct
{
  xREG            REG;

  int fd;
	char buf[MAX_BUF_SZ];
	char url[1024];
	char uri[2][1024];
  XMTIFHttp  m;
  void* info;
  void* pif;
} mtifHttp;


int http_status(void*,void*,void*,void*);



#define TELBOT_API   "http://api.telegram.org/bot368941440:AAGGCZ9NFqyY55wnqRBU87riCp4sMbvZS0s/sendMessage?chat_id=330973088&text=NEO3"

#endif
