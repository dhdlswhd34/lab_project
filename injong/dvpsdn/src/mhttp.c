#include <mcommon.h>
#include <mhttp.h>

// ?CID=C&DATA=FE+7B+01+02+03+FF


void* on_http_status(void* t,int fd,unsigned char* b,int sz,void* mi,int err,void* o)
{
  SYSTEM_LOG(0, 0, "on_http_status %08X\r\n", err);

  switch(err)
  {
    case 0xE000C00A:
      xmsgq_set(t, MAKELONG(WRITE, XHTTP), 0, 0);
      break;
  }


  return 0;
}
void* on_http_read(void* t,int fd,unsigned char* b,int sz,void* mi,int err,void* o)
{
  if ( sz > 0 )
  fprint_buffer("on_http_read", b, sz, 0, 16);

  /***
  tagMTIFHTTP* phttp = (tagMTIFHTTP*)o;
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\r\n");
  printf("on_http_recvex %d, %s, %d, %s, %d\r\n",sd, b, sz, ip, port);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\r\n");
  ***/
  return 0;
}


int http_write(void* t, void* msg, void* wparam, void* lparam)
{
	int i = 0;
	int e = 0;
  char url[1024];
	char hdr[1024];
	char kv[1024];
  mtifHttp* p = (mtifHttp*)t;
	
	if(p->fd==0) return -1;
  sprintf(p->url, "http://%s:%s%s",
              ((mtifInfo*)p->info)->arg[XHTTP][XM_IP],
              ((mtifInfo*)p->info)->arg[XHTTP][XM_PORT],
              ((mtifInfo*)p->info)->arg[XHTTP][XM_URI]);
	SYSTEM_LOG(0, 0, "Request %s\r\n", p->url);

  e = mtifHttpReq(&p->m, p->url, 0);
  SYSTEM_LOG(0, 0, "WRITE COMPLETED %08X\r\n", e);

	//
	//sprintf(kv, "?cid=c&data=");
	//e = strlen(kv);
	//for ( i=0 ; i<(int)(lparam); i++)
	//{
	//	sprintf(&kv[e], "%02X+", *(p+i));
	//	e+=3;
	//}
	//*(kv+e-1) = 0;
	//sprintf(url, "%s%s", phttp->url, kv);
 // SYSTEM_LOG(0, 0, "%s \r\n", url);
	//#if 0
 // sprintf(hdr,
 //         "GET /%s HTTP/%s\r\n"
 //         "Accept: text/html, "
 //         //"application/xhtml+xml, "
 //         //"image/jxr, "
 //         "*/*\r\n"
 //         "Accept-Language: ko-KR\r\n"
 //         //"User-Agent: Mozilla/5.0\r\n"
 //         //"Accept-Encoding: gzip, deflate\r\n"
	//				"Host: %s\r\n"
 //         "Connection: Keep-Alive\r\n"
	//				"\r\n"
	//				,url 
	//				,HTTP_PROTOCOL_VER
	//				,((tagMTIFInfo*)phttp->info)->arg[XHTTP][XM_IP]
	//				);
	//printf("%s\r\n", hdr);
	//#endif
	//e = mtifHttpReqValEx(&phttp->m, "GET", url, 0, 0, 0);

  return 0;
}

int http_open(void* t, void* msg, void* wparam, void* lparam)
{
	int sz = MAX_BUF_SZ;
  mtifHttp* p = (mtifHttp*)t;
  p->buf[0] = 0x80|0x0C;  // 1<<12
  p->m.pfxMTIF[ONHTTPSTATUS] = on_http_status;
  p->m.pfxMTIF[ONHTTPREAD]   = on_http_read;
  sprintf(p->url, "http://%s:%s%s",
                ((mtifInfo*)p->info)->arg[XHTTP][XM_IP],
                ((mtifInfo*)p->info)->arg[XHTTP][XM_PORT],
                ((mtifInfo*)p->info)->arg[XHTTP][XM_URI]);
  SYSTEM_LOG(0, 0, "HTTP Open %s \r\n", p->url);

	mtifHttpGetURL(&p->m, p->url, p->uri[0], p->uri[1]);
  SYSTEM_LOG(0, 0, "HTTP %s %s\r\n", p->uri[0], p->uri[1]);

  p->fd = mtifHttpOpen(&p->m,p->url,p->buf,p);
  SYSTEM_LOG(0, 0, "HTTP %d connected\r\n", p->fd);

  return p->fd;
}

int http_close(void* t, void* msg, void* wparam, void* lparam)
{
  mtifHttpClose(&((mtifHttp*)t)->m, ((mtifHttp*)t)->buf);
  ((mtifHttp*)t)->m.pfxMTIF[ONHTTPSTATUS] = 0;
  ((mtifHttp*)t)->m.pfxMTIF[ONHTTPREAD]   = 0;
  ((mtifHttp*)t)->fd = 0;
  SYSTEM_LOG(0, 0, "HTTP close\r\n");
  return ((mtifHttp*)t)->fd;
}


int http_init(void* t, void* msg, void* wparam, void* lparam)
{
  int e = 0;
  mtifHttp* p = (mtifHttp*)t;
  p->info = wparam;

  e = mtifHttpCreate(&p->m);
  if ( e < 0 )
  {
    SYSTEM_LOG(0, 0, "HTTP Create Fail %s, %s, %s\r\n",
                ((mtifInfo*)p->info)->arg[XHTTP][XM_IP],
                ((mtifInfo*)p->info)->arg[XHTTP][XM_PORT],
                ((mtifInfo*)p->info)->arg[XHTTP][XM_URI]);
    return -1;
  }
  SYSTEM_LOG(0, 0, "HTTP Create Success %s, %s, %s\r\n",
              ((mtifInfo*)p->info)->arg[XHTTP][XM_IP],
              ((mtifInfo*)p->info)->arg[XHTTP][XM_PORT],
              ((mtifInfo*)p->info)->arg[XHTTP][XM_URI]);

  xmsgq_set(t, MAKELONG(OPEN, XHTTP), wparam, lparam);
  return 0;
}

int http_release(void* t, void* msg, void* wparam, void* lparam)
{
  mtifHttpDestroy( &((mtifHttp*)t)->m );
  SYSTEM_LOG(0, 0, "HTTP Destroy Success %s, %s, %s\r\n",
              ((mtifInfo*)((mtifHttp*)t)->info)->arg[XHTTP][XM_IP],
              ((mtifInfo*)((mtifHttp*)t)->info)->arg[XHTTP][XM_PORT],
              ((mtifInfo*)((mtifHttp*)t)->info)->arg[XHTTP][XM_URI]);
  return 0;
}


int http_idle(void* t, void* msg, void* wparam, void* lparam)
{
  //int max_cnt = atoi(lparam);
  //if ( phttp->REG.COUNTER[0] == 0 )
  //{
  //  printf("\r\n");
  //}
  //if ( (phttp->REG.COUNTER[0]%1000) == 0 )
  //{
  //  printf(".");
  //}
  //phttp->REG.COUNTER[0]++;
  //if (phttp->REG.COUNTER[0] >= (max_cnt*COUNT_CALI))
  //{
  //  xmsgq_set(t, wparam, 0, 0);
  //  phttp->REG.COUNTER[0] = 0;
  //  printf("\r\n");
  //}
  //else
  //{
  //  xmsgq_set(t, msg, wparam, lparam);
  //}
  return 0;
}


int http_status(void* t, void* msg, void* wparam, void* lparam)
{
  switch(LOWORD((unsigned int)msg))
  {
    case INIT:
      http_init(t, msg, wparam, lparam);
      break;
    case RELEASE:
      http_release(t, msg, wparam, lparam);
      break;
    case OPEN:
      http_open(t, msg, wparam, lparam);
      break;
    case CLOSE:
      http_close(t, msg, wparam, lparam);
      break;
    case WRITE:
      http_write(t, msg, wparam, lparam);
      break;
    case IDLE:
      http_idle(t, msg, wparam, lparam);
      break;
  }
  return 0;
}

