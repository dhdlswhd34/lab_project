#include <mcommon.h>
#include <msocket.h>

static mtifSocket* g;

char sample_char = 'A';
int sample_count = 0;
const char* sample_delay = "10000";

int socket_broadcast(void* t, void* msg, void* wparam, void* lparam)
{
  int e = 0;
  int i = 0;
  int s = 0;
  fprint_buffer("socket_broadcast", (char*)lparam, (int)wparam, 0, 16);
  if ( ((mtifInfo*)g->info)->arg[XSOCKET][XM_CSTYPE][0] == 'S' )
  {
    s=mtifSocketFDSet(&g->m, (void**)&g->fds);
    for (i=0 ; i<s ; i++ )
    {
      if ( (g->fds+i)->a[0] > 0 )
      {
        e = mtifSocketWrite(&g->m, (g->fds+i)->a[0], (char*)lparam, (int)wparam);
        SYSTEM_LOG(0, 0, "[%4d:%4d] %d\r\n", i, (g->fds+i)->a[0], e);
      }
    }
  }

  return 0;
}


int socket_write(void* t, void* msg, void* wparam, void* lparam)
{
  int e = 0;

  fprint_buffer("socket_write", (char*)((mtifSocket*)t)->pack.info[(int)lparam].b, (int)wparam, 0, 16);

  e = mtifSocketWrite(&((mtifSocket*)t)->m, ((mtifSocket*)t)->pack.info[(int)lparam].fd, ((mtifSocket*)t)->pack.info[(int)lparam].b, (int)wparam);

  SYSTEM_LOG(0, 0, "socket_write result %d %d\r\n", e, (int)wparam);

  return 0;
}

void display_fdset(fdsetex* p, int sz)
{
  int i=0;
  for ( i=0 ; i<sz ; i++ )
  {
    if ( (i%4) == 0 ) printf("\r\n");
    printf(" [%4d,%4d] ", (p+i)->a[0], (p+i)->a[1]);
  }
}



void* on_socket_status(void* t,int fd,unsigned char* b,int sz,void* mi,int err,void* o)
{
  int e = 0;
  SYSTEM_LOG(0, 0, "[%08X] \r\n", err);
  switch(err)
  {
    case 0xE000ACCB:
      if(((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S')
      {
        ((mtifSocket*)o)->pack.info[(int)mi].b[0] = 0x80|SOCKET_BUF_SFT;
        *(char**)b = ((mtifSocket*)o)->pack.info[(int)mi].b;
        ((mtifSocket*)o)->pack.info[(int)mi].fd = fd;
      }
      break;
    case 0xE000ACCA:
      if(((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S')
      {
        e=mtifSocketFDSet(&((mtifSocket*)o)->m,(void**)&(((mtifSocket*)o)->fds));
        display_fdset(((mtifSocket*)o)->fds,e);
      }
      break;
    case 0xE000101A:
      if(((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S')
      {
        e=mtifSocketFDSet(&((mtifSocket*)o)->m,(void**)&(((mtifSocket*)o)->fds));
        display_fdset(((mtifSocket*)o)->fds,e);
        e = 0;
      }
      break;
    case 0xE000500F:
    case 0xE000101F:
      if(((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='C')
      {
        xmsgq_set(o, MAKELONG(CLOSE, XSOCKET), 0, 0);
        xmsgq_set(o, MAKELONG(IDLE, XSOCKET), MAKELONG(OPEN, XSOCKET), (void*)((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_DELAY_0]);
      }
      break;
    case 0xE000001A:
      if(((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S')
      {
        if(((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_ECHOMODE][0]=='1')
        {
          xmsgq_set(o, MAKELONG(WRITE, XSOCKET), (void*)sz, mi);
        }
      }
      break;
    case 0xE00010BF:
      if(((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S')
      {
        //((mtifSocket*)o)->pack.info[(int)mi].b[0]=0x80|SOCKET_BUF_SFT;
        //*(char**)b = ((mtifSocket*)o)->pack.info[(int)mi].b;
        //e = 1;
      }
      break;
  }
  return (void*)e;
}
void* on_socket_read(void* t,int fd,unsigned char* b,int sz,void* mi,int err,void* o)
{

  if ( sz <= 0 ) return 0;
  SYSTEM_LOG(0, 0, "on_socket_read %d \r\n", fd);

  //fprint_buffer("on_socket_read",b, sz, 0, 16);

  if(((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S')
  {
    fprint_buffer("on_socket_read",((mtifSocket*)o)->pack.info[(int)mi].b,sz,0,16);
    xmsgq_set(o, MAKELONG(BROADCAST, XWEBSOCKET), (void*)sz, (void*)((mtifSocket*)o)->pack.info[(int)mi].b);
  }


  return 0;
}


int socket_open(void* t, void* msg, void* wparam, void* lparam)
{
	int e = 0;
  int sz = MAX_BUF_SZ;
  mtifSocket* p = (mtifSocket*)t;
  SYSTEM_LOG(0, 0, "mtifSocketOpen %s, %s, %s, %s, %s\r\n",
              ((mtifInfo*)p->info)->arg[XSOCKET][XM_IP],
              ((mtifInfo*)p->info)->arg[XSOCKET][XM_PORT],
              ((mtifInfo*)p->info)->arg[XSOCKET][XM_PROTO],
              ((mtifInfo*)p->info)->arg[XSOCKET][XM_CSTYPE],
              ((mtifInfo*)p->info)->arg[XSOCKET][XM_DELAY_0]);
  p->m.pfxMTIF[ONSOCKETSTATUS] = on_socket_status;
  p->m.pfxMTIF[ONSOCKETREAD]   = on_socket_read;
  //memcpy(p->pack.info[0].buf, &sz, sizeof(int));
  p->pack.info[0].b[0] = 0x80|SOCKET_BUF_SFT;

  p->fd = mtifSocketOpen(&p->m,
              ((mtifInfo*)p->info)->arg[XSOCKET][XM_IP],
              ((mtifInfo*)p->info)->arg[XSOCKET][XM_PORT],
              ((mtifInfo*)p->info)->arg[XSOCKET][XM_CSTYPE],
              ((mtifInfo*)p->info)->arg[XSOCKET][XM_PROTO],
              ((mtifInfo*)p->info)->arg[XSOCKET][XM_CASTTYPE],
              p->pack.info[0].b,
              p);

  if ( p->fd > 0)
  {
    SYSTEM_LOG(0, 0, "Socket Open SUCCESS[%d], %s, %s, %s, %s\r\n",
                p->fd,
                ((mtifInfo*)p->info)->arg[XSOCKET][XM_IP],
                ((mtifInfo*)p->info)->arg[XSOCKET][XM_PORT],
                ((mtifInfo*)p->info)->arg[XSOCKET][XM_PROTO],
                ((mtifInfo*)p->info)->arg[XSOCKET][XM_CSTYPE]);
  }
  else
  {
    SYSTEM_LOG(0, 0, "Socket Open Fail[%d], %s, %s, %s, %s\r\n",
                p->fd,
                ((mtifInfo*)p->info)->arg[XSOCKET][XM_IP],
                ((mtifInfo*)p->info)->arg[XSOCKET][XM_PORT],
                ((mtifInfo*)p->info)->arg[XSOCKET][XM_PROTO],
                ((mtifInfo*)p->info)->arg[XSOCKET][XM_CSTYPE]);
  }
  return 0;
}

int socket_close(void* t, void* msg, void* wparam, void* lparam)
{
  mtifSocket* p = (mtifSocket*)t;
  p->m.pfxMTIF[ONSOCKETSTATUS] = 0;
  p->m.pfxMTIF[ONSOCKETREAD] = 0;

  mtifSocketClose(&p->m, p->pack.info[0].b);
  SYSTEM_LOG(0, 0, "Socket Close \r\n");
  return 0;
}

int socket_init(void* t, void* msg, void* wparam, void* lparam)
{
	int e = 0;
  mtifSocket* p = (mtifSocket*)t;
  g = p;
  p->info = wparam;

  p->m.key = "shinbaad@gmail.com";

  e = mtifSocketCreate(&p->m);
  if ( e<0 )
  {
    return -1;
  }

  SYSTEM_LOG(0, 0, "Socket Create Success[%d] \r\n", e);

  p->REG.COUNTER[0] = 0;

  xmsgq_set(t, MAKELONG(OPEN, XSOCKET), wparam, lparam);
  return 0;
}

int socket_release(void* t, void* msg, void* wparam, void* lparam)
{
	int e = 0;
  mtifSocket* p = (mtifSocket*)t;

  p->m.pfxMTIF[ONSOCKETSTATUS] = 0;
  p->m.pfxMTIF[ONSOCKETREAD] = 0;

  e = mtifSocketDestroy(&p->m);
  if ( e<0 )
  {
    return -1;
  }

  SYSTEM_LOG(0, 0, "Socket Destroy Success[%d] \r\n", e);

  return 0;
}

int socket_idle(void* t, void* msg, void* wparam, void* lparam)
{
  mtifSocket* p = (mtifSocket*)t;
  int max_cnt = atoi(lparam);

  p->REG.COUNTER[0]++;


  if (p->REG.COUNTER[0] >= (max_cnt*COUNT_CALI))
  {
    xmsgq_set(t, wparam, 0, 0);
    p->REG.COUNTER[0] = 0;
  }
  else
  {
    xmsgq_set(t, msg, wparam, lparam);
  }
  return 0;
}

int socket_status(void* t, void* msg, void* wparam, void* lparam)
{
  switch(LOWORD((unsigned int)msg))
  {
    case INIT:
      socket_init(t, msg, wparam, lparam);
      break;
    case RELEASE:
      socket_release(t, msg, wparam, lparam);
      break;
    case OPEN:
      socket_open(t, msg, wparam, lparam);
      break;
    case CLOSE:
      socket_close(t, msg, wparam, lparam);
      break;
    case WRITE:
      socket_write(t, msg, wparam, lparam);
      break;
    case BROADCAST:
      socket_broadcast(t, msg, wparam, lparam);
      break;
    case IDLE:
      socket_idle(t, msg, wparam, lparam);
      break;
      
  }
  return 0;
}

