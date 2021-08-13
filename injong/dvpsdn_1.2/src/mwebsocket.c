#include <mcommon.h>
#include <mwebsocket.h>

static mtifWebSocket* g;

int websocket_broadcast(void* t, void* msg, void* wparam, void* lparam)
{
  int e = 0;
  int i = 0;
  int s = 0;
  fprint_buffer("websocket_broadcast", (char*)lparam, (int)wparam, 0, 16);
  if ( ((mtifInfo*)g->info)->arg[XWEBSOCKET][XM_CSTYPE][0] == 'S' )
  {
    s=mtifWebSocketClientSet(&g->m, (void**)&g->cs);
    for (i=0 ; i<s ; i++ )
    {
      if ( (g->cs+i)->fd > 0 )
      {
        e = mtifWebSocketWrite(&g->m, (g->cs+i)->fd, (char*)lparam,(int)wparam);
        if ( e > 0 ) SYSTEM_LOG(0, 0, "[%4d:%4d] %d\r\n", i, (g->cs+i)->fd, e);
      }
    }
  }
  return 0;
}

int websocket_write(void* t, void* msg, void* wparam, void* lparam)
{
  int e = 0;
  unsigned char* lp = (unsigned char*)wparam;
  //if ( p->sd > 0 )
  //{
  //  SYSTEM_LOG(0, 0, "send %d\r\n", (int)lparam);
  //  display_buffer("websocket write", (char*)wparam, (int)lparam);
  //  e = mtifWebSocketWriteEx(&p->m, p->sd, (char*)wparam, (int)lparam);
  //  //e = mtifWebSocketSendEx(&p->m, p->sd, (char*)wparam, (int)lparam, *(lp+0)>0x7F?0x02:0x01, 0, 1);
  //}

  #if 0
  mcsleep(1000000);
  printf("Write ----> \r\n");
  sprintf(buf, "%c0000^%d^%d^%c%d.%d%d^%c%d.%d%d%c",
          STX, rand()%100, rand()%100,
          rand()%2==0?' ':'-',
          rand()%90, rand()%10000, rand()%10000,
          rand()%2==0?' ':'-',
          rand()%180, rand()%10000, rand()%10000,
          ETX);

  e = mtifWebSocketSendEx(&p->m, p->sd, buf, strlen(buf), 0, 1);
	printf("mtifWebSocketSendEx : %d \r\n", e);
  //xmsgq_set(WEB_SOCKET, WRITE, 0, lparam);
  #endif
  return 0;
}

void display_clientset(wsClientSet* p, int sz)
{
  int i;
  for ( i=0 ; i<sz ; i++ )
  {
    if ( i && (i%4)==0 ) printf("\r\n");
    printf("[%08X] ", (unsigned int)(p+i)->fd);
  }
  printf("\r\n");
}
void wsdisplay_fdset(wsFDSet* p, int sz)
{
  int i;
  for ( i=0 ; i<sz ; i++ )
  {
    if ( i && (i%4)==0 ) printf("\r\n");
    //printf("[%08X] ", (unsigned int)(p+i)->a[0]);
  }
  printf("\r\n");
}


void* on_websocket_status(void* t,int fd,unsigned char* b,int sz,void* mi,int err,void* o)
{
  int e = 0;
  SYSTEM_LOG(0,0,"WebSocket status %d %d (%12d) %08X\r\n",fd,(int)mi, sz, err);
 
  switch(err)
  {
    case 0xE000ACCB:
      if ( ((mtifInfo*)((mtifWebSocket*)o)->info)->arg[XWEBSOCKET][XM_CSTYPE][0]=='S' )
      {
        ((mtifWebSocket*)o)->pack.info[(int)mi].fd = fd;
        ((mtifWebSocket*)o)->pack.info[(int)mi].buf[0] = 0x80|WEBSOCKET_BUF_SFT;
        *((char**)b) = ((mtifWebSocket*)o)->pack.info[(int)mi].buf;
        SYSTEM_LOG(0,0,"Client [%4d] Connected at %4d\r\n", fd, (int)mi);
      
      }
      break;

    case 0xE000101F:
      if ( ((mtifInfo*)((mtifWebSocket*)o)->info)->arg[XWEBSOCKET][XM_CSTYPE][0]=='S' )
      {
        int e = 0;
        ((mtifWebSocket*)o)->pack.info[(int)mi].fd = 0;
        ((mtifWebSocket*)o)->pack.info[(int)mi].buf[0] = 0;
        SYSTEM_LOG(0,0,"Client [%4d] Disrconnected at %4d\r\n", fd, (int)mi);
      }
      break;

    case 0xE000B0FF:
      *((char**)b) = ((mtifWebSocket*)o)->iobuf;
      break;

    case 0xE00010BF:
      //((mtifWebSocket*)o)->pack.info[(int)mi].buf[0] = WEBSOCKET_BUF_SFT;
      //*((char**)b) = ((mtifWebSocket*)o)->pack.info[(int)mi].buf;
      //e = 1;
      break;

  }

  return (void*)e;
}

void* on_websocket_read(void* t,int fd,unsigned char* b,int sz,void* mi,int err,void* o)
{
  mtifWebSocket* p = (mtifWebSocket*)t;
  char rbuf[1024];
  int i ,e=0;
  SYSTEM_LOG(0,0,"WebSocket status %d %d (%12d) %08X\r\n", fd, (int)mi, sz, err);
  SYSTEM_LOG(0,0,"WebSocket read %c \r\n", *b);
  fprint_buffer("websocket_broadcast", b, 26, 0, 16);
  
  e = mtifWebSocketRead(&p->m,fd,rbuf,26);
  if( e < 0) return;
  printf("mtifWebSocketRead: e : %d (%08X) \r\n", e, e);
  for ( i=0 ; i<26 ; i++ )
	{
		printf(" rbuf[%d] : %c \r\n", i, rbuf[i]);
	}
  fprint_buffer("------------>",rbuf, 26, 0, 16);
  return 0;
}


int websocket_open(void* t, void* msg, void* wparam, void* lparam)
{
	int e = 0;
  char host[128];
  char url[256];
  int sz = WS_MAX_BUF_SZ;
  mtifWebSocket* p = (mtifWebSocket*)t;

  p->pack.info[0].buf[0] = 0x80|WEBSOCKET_BUF_SFT;
  sprintf(host, "http://%s:%s/",
                ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_IP],
                ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_PORT]);
  p->m.pfxMTIF[ONWSSTATUS] = on_websocket_status;
  p->m.pfxMTIF[ONWSREAD]   = on_websocket_read;

  p->fd = mtifWebSocketOpen(&p->m,host,((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_CSTYPE],0,p->pbuf,0,p);
  if ( p->fd < 0 )
  {
    SYSTEM_LOG(0, 0, "WebSocket Open Fail [%d], %s, %s, %s\r\n",
                p->fd,
                ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_IP],
                ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_PORT],
                ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_CSTYPE]);
    return -1;
  }
  SYSTEM_LOG(0, 0, "WebSocket Open Success [%d], %s, %s, %s\r\n",
              p->fd,
              ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_IP],
              ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_PORT],
              ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_CSTYPE]);

  return 0;
}

int websocket_close(void* t, void* msg, void* wparam, void* lparam)
{
  mtifWebSocket* p = (mtifWebSocket*)t;
  mtifWebSocketClose(&p->m, p->pbuf);
  p->m.pfxMTIF[ONWSSTATUS] = 0;
  p->m.pfxMTIF[ONWSREAD]   = 0;

  return 0;
}


int websocket_init(void* t, void* msg, void* wparam, void* lparam)
{
	int e = 0;
  char host[128];
  mtifWebSocket* p = (mtifWebSocket*)t;
  g = p;
  p->info = wparam;
  p->m.key = "shinbaad@gmail.com";
  e = mtifWebSocketCreate(&p->m);
  if ( e<0 )
  {
    SYSTEM_LOG(0, 0, "WebSocket Create Fail %s, %s, %s\r\n",
                ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_IP],
                ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_PORT],
                ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_CSTYPE]);
    return -1;
  }
  SYSTEM_LOG(0, 0, "WebSocket Create Success %s, %s, %s\r\n",
              ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_IP],
              ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_PORT],
              ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_CSTYPE]);

  xmsgq_set(t, MAKELONG(OPEN, XWEBSOCKET), wparam, lparam);
              
  return 0;
}
int websocket_release(void* t, void* msg, void* wparam, void* lparam)
{
  mtifWebSocketDestroy(&((mtifWebSocket*)t)->m);
  return 0;
}


int websocket_status(void* t, void* msg, void* wparam, void* lparam)
{
  switch(LOWORD((unsigned int)msg))
  {
    case INIT:
      websocket_init(t, msg, wparam, lparam);
      break;
    case RELEASE:
      websocket_release(t, msg, wparam, lparam);
      break;
    case OPEN:
      websocket_open(t, msg, wparam, lparam);
      break;
    case CLOSE:
      websocket_close(t, msg, wparam, lparam);
      break;
    case WRITE:
      websocket_write(t, msg, wparam, lparam);
      break;
    case BROADCAST:
      websocket_broadcast(t, msg, wparam, lparam);
      break;
  }
  return 0;
}

