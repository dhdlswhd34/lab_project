#include <mcommon.h>
#include <mhttpd.h>

// ?CID=C&DATA=FE+7B+01+02+03+FF


void* on_httpd_status(void* t,int fd,unsigned char* b,int sz,void* mi,int err,void* o)
{
  //SYSTEM_LOG(0, 0, "on_http_status %08X\r\n", err);

  return 0;
}
void* on_httpd_read(void* t,int fd,unsigned char* b,int sz,void* mi,int err,void* o)
{
  //if ( sz > 0 ) fprint_buffer("on_http_read", b, sz, 0, 16);

  /***
  tagMTIFHTTP* phttp = (tagMTIFHTTP*)o;
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\r\n");
  printf("on_http_recvex %d, %s, %d, %s, %d\r\n",sd, b, sz, ip, port);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\r\n");
  ***/
  return 0;
}


int httpd_write(void* t, void* msg, void* wparam, void* lparam)
{
	int i = 0;
	int e = 0;
  char url[1024];
	char hdr[1024];
	char kv[1024];


  return 0;
}

int httpd_open(void* t, void* msg, void* wparam, void* lparam)
{
	int sz = MAX_BUF_SZ;
  mtifHttpd* p = (mtifHttpd*)t;

  mtifHttpSetConfig(&p->m, "home", ((mtifInfo*)p->info)->arg[XHTTPD][XM_HOME]);
  mtifHttpSetConfig(&p->m, "index", ((mtifInfo*)p->info)->arg[XHTTPD][XM_INDEX]);

  p->buf[0] = 0x80|0x0C;  // 1<<12
  p->m.pfxMTIF[ONHTTPSTATUS] = on_httpd_status;
  p->m.pfxMTIF[ONHTTPREAD]   = on_httpd_read;
  sprintf(p->url, "http://%s:%s",
                ((mtifInfo*)p->info)->arg[XHTTPD][XM_IP],
                ((mtifInfo*)p->info)->arg[XHTTPD][XM_PORT]);
  SYSTEM_LOG(0, 0, "HTTPD Open %s \r\n", p->url);

  p->fd = mtifHttpOpen(&p->m, "SERVER", p->url, p->buf, &p->m);

  SYSTEM_LOG(0, 0, "HTTPD Open SUCCESS \r\n");


  return p->fd;
}

int httpd_close(void* t, void* msg, void* wparam, void* lparam)
{
  mtifHttpClose(&((mtifHttpd*)t)->m, ((mtifHttpd*)t)->buf);
  ((mtifHttpd*)t)->m.pfxMTIF[ONHTTPSTATUS] = 0;
  ((mtifHttpd*)t)->m.pfxMTIF[ONHTTPREAD]   = 0;
  ((mtifHttpd*)t)->fd = 0;
  SYSTEM_LOG(0, 0, "HTTP close\r\n");
  return ((mtifHttpd*)t)->fd;
}


int httpd_init(void* t, void* msg, void* wparam, void* lparam)
{
  int e = 0;
  mtifHttpd* p = (mtifHttpd*)t;
  p->info = wparam;

  p->m.key = "shinbaad@gmail.com";
  e = mtifHttpCreate(&p->m);
  if ( e < 0 )
  {
    SYSTEM_LOG(0, 0, "HTTPD Create Fail %s, %s, %s, %s\r\n",
                ((mtifInfo*)p->info)->arg[XHTTPD][XM_IP],
                ((mtifInfo*)p->info)->arg[XHTTPD][XM_PORT],
                ((mtifInfo*)p->info)->arg[XHTTPD][XM_HOME],
                ((mtifInfo*)p->info)->arg[XHTTPD][XM_INDEX]);
    return -1;
  }
  SYSTEM_LOG(0, 0, "HTTPD Create Success %s, %s, %s, %s\r\n",
                ((mtifInfo*)p->info)->arg[XHTTPD][XM_IP],
                ((mtifInfo*)p->info)->arg[XHTTPD][XM_PORT],
                ((mtifInfo*)p->info)->arg[XHTTPD][XM_HOME],
                ((mtifInfo*)p->info)->arg[XHTTPD][XM_INDEX]);
  xmsgq_set(t, MAKELONG(OPEN, XHTTPD), wparam, lparam);
  return 0;
}

int httpd_release(void* t, void* msg, void* wparam, void* lparam)
{
  mtifHttpDestroy( &((mtifHttpd*)t)->m );
  SYSTEM_LOG(0, 0, "HTTPD Destroy Success %s, %s, %s, %s\r\n",
              ((mtifInfo*)((mtifHttpd*)t)->info)->arg[XHTTP][XM_IP],
              ((mtifInfo*)((mtifHttpd*)t)->info)->arg[XHTTP][XM_PORT],
              ((mtifInfo*)((mtifHttpd*)t)->info)->arg[XHTTP][XM_HOME],
              ((mtifInfo*)((mtifHttpd*)t)->info)->arg[XHTTP][XM_INDEX]);
  return 0;
}


int httpd_idle(void* t, void* msg, void* wparam, void* lparam)
{
  return 0;
}


int httpd_status(void* t, void* msg, void* wparam, void* lparam)
{
  switch(LOWORD((unsigned int)msg))
  {
    case INIT:
      httpd_init(t, msg, wparam, lparam);
      break;
    case RELEASE:
      httpd_release(t, msg, wparam, lparam);
      break;
    case OPEN:
      httpd_open(t, msg, wparam, lparam);
      break;
    case CLOSE:
      httpd_close(t, msg, wparam, lparam);
      break;
    case WRITE:
      httpd_write(t, msg, wparam, lparam);
      break;
    case IDLE:
      httpd_idle(t, msg, wparam, lparam);
      break;
  }
  return 0;
}

