
#include <mcommon.h>
#include <xm.h>
#include <mpacket.h>
#include <mtifSHM.h>


int packet_write(void* t, void* msg, void* wparam, void* lparam)
{
  return 0;
}

void* on_packet_status(void* t,int fd,unsigned char* b,int sz,void* mi,int err,void* o)
{

  int e  = 0;
  int ea = 1;
	mtifPacket* pkt = (mtifPacket*)o;
	MTIF*       pif = (MTIF*)pkt->pif;
	
  SYSTEM_LOG(0, 0, "on_packet_status 0x%08X \r\n", err);

#if 1
  if ( err == 0xE00010BF )
  {
    pkt->qidx++;
    pkt->qidx %= pif->mshm.cnt;
    SYSTEM_LOG(0, 0, "qidx:%4d, cnt:%4d, sz:%4d,%4d \r\n",
																	pkt->qidx, pif->mshm.cnt, pif->mshm.sz,pif->mshm_s.sz);
		SYSTEM_LOG(0, 0, "%p \r\n", pif->mshm.p);

    (pif->mshm.p+((pkt->qidx)*(pif->mshm.sz)))[0] = 0x80|10;
    *(char**)b = (pif->mshm.p + ((pkt->qidx)*(pif->mshm.sz)) );

    pif->mshm_s.p = (pif->mshm_s.p+((pkt->qidx)*(pif->mshm_s.sz)));

    SYSTEM_LOG(0, 0, "pkt->qidx -> %d \r\n", pkt->qidx);
   
		#if 0
    if(((mtifPacket*)o)->qidx == 19)
    {
      SYSTEM_LOG(0, 0, "((mtifPacket*)o)->qidx -> %d    stop!!! \r\n", ((mtifPacket*)o)->qidx);
      sleep(1);
      //exit(1);
    }
		#endif
    e = 1;
  }
#endif

#if 0 //// injong
  if ( err == 0xE00010BF )
  {
    pkt->qidx++;
    pkt->qidx %= pif->mshm.cnt;
    (((MTIF*)((mtifPacket*)o)->pif)->mshm.p+((mtifPacket*)o)->qidx*(((MTIF*)((mtifPacket*)o)->pif)->mshm.sz))[0] = 0x80|17;
    (((MTIF*)((mtifPacket*)o)->pif)->mshm_s.p+((mtifPacket*)o)->qidx*(((MTIF*)((mtifPacket*)o)->pif)->mshm_s.sz))[0] = 0x80|10;

    //*((MTIF*)((mtifPacket*)o)->pif)->mshm.p = sz;
    *(char**)b = (((MTIF*)((mtifPacket*)o)->pif)->mshm.p +  ((mtifPacket*)o)->qidx*(((MTIF*)((mtifPacket*)o)->pif)->mshm.sz) );
    SYSTEM_LOG(0, 0, "((mtifPacket*)o)->qidx -> %d \r\n", ((mtifPacket*)o)->qidx);
   
    if(((mtifPacket*)o)->qidx == 19)
    {
      SYSTEM_LOG(0, 0, "((mtifPacket*)o)->qidx -> %d    stop!!! \r\n", ((mtifPacket*)o)->qidx);
      sleep(1);
      //exit(1);
    }

    #if 0
    *(((MTIF*)((mtifPacket*)o)->pif)->mshm_s.p) =  1;
    ((MTIF*)((mtifPacket*)o)->pif)->mshm.p = (((MTIF*)((mtifPacket*)o)->pif)->mshm_s.p+1);
    #endif

    /****
    ((mtifPacket*)o)->qidx = (++(((mtifPacket*)o)->qidx))%MAX_BUF_QUE;
    ((mtifPacket*)o)->b[((mtifPacket*)o)->qidx][0] = MAX_BUF_SZ;
    *(char**)b = ((mtifPacket*)o)->b[((mtifPacket*)o)->qidx];
    ****/
    //fprint_buffer("on_packet_read",(((MTIF*)((mtifPacket*)o)->pif)->mshm.p), sz, 0, 16);
    //fprint_buffer("on_packet_read--",(((MTIF*)((mtifPacket*)o)->pif)->mshm_s.p), sz, 0, 16);
    e = 1;
    //SYSTEM_LOG(0, 0, "%08X -> %08X \r\n", ((mtifPacket*)o)->b[((mtifPacket*)o)->qidx-1], ((mtifPacket*)o)->b[((mtifPacket*)o)->qidx]);
  }

#endif


  return (void*)e;
}

void* on_packet_read(void* t,int fd,unsigned char* b,int sz,void* mi,int err,void* o)
{
  int e= 0 ;
  mtifPacket* pkt = (mtifPacket*)o;
  MTIF*       pif = (MTIF*)pkt->pif;

  if ( err<0 ) return on_packet_status(t,fd,b,sz,mi,err,o);
  if ( sz <= 0 ) return 0;

  fprint_buffer("on_packet_read_b",b, sz, 0, 16);

  

#if 0
  SYSTEM_LOG(0, 0, "%08X  on_packet_read %d %d \r\n", b,fd,sz);
  fprint_buffer("on_packet_read_b",b, sz, 0, 16);

  //(b+16) = (((MTIF*)((mtifPacket*)o)->pif)->mshm_s.p);
  *(((MTIF*)((mtifPacket*)o)->pif)->mshm_s.p) = *(b+16); /// tcp hdr + bdy;
  fprint_buffer("on_packet_read_sub",(((MTIF*)((mtifPacket*)o)->pif)->mshm_s.p), 4  , 0, 16);
#endif
  
#if 0
  *(((MTIF*)((mtifPacket*)o)->pif)->mshm_s.p) =  1;
  ((MTIF*)((mtifPacket*)o)->pif)->mshm.p = (((MTIF*)((mtifPacket*)o)->pif)->mshm_s.p+1);
  
  fprint_buffer("on_packet_read--",(((MTIF*)((mtifPacket*)o)->pif)->mshm_s.p), 32, 0, 16);  
#endif

  return 0;
}


int packet_open(void* t, void* msg, void* wparam, void* lparam)
{
	int e = 1;
  int sz = MAX_BUF_SZ;
  mtifPacket* p = (mtifPacket*)t;
  SYSTEM_LOG(0, 0, "mtifPacketOpen %s %s\r\n",
              ((mtifInfo*)p->info)->arg[XPACKET][XM_IFNAME],
              ((mtifInfo*)p->info)->arg[XPACKET][XM_DELAY_0]);

  
 ((MTIF*)p->pif)->mshm.p[0] = 0x80|17;
  p->m.pfxMTIF[ONPACKETREAD]   = on_packet_read;
  p->fd = mtifPacketOpen(&p->m,
              ((mtifInfo*)p->info)->arg[XPACKET][XM_IFNAME],
              ((MTIF*)p->pif)->mshm.p,
              p);
  SYSTEM_LOG(0, 0, "mtifPacketOpen %d\r\n", p->fd);
  if ( p->fd > 0)
  {
    SYSTEM_LOG(0, 0, "Packet Open Success[%d], %s\r\n", p->fd,((mtifInfo*)p->info)->arg[XPACKET][XM_IFNAME]);
  }
  else
  {
    SYSTEM_LOG(0, 0, "Packet Open Fail[%d], %s\r\n", p->fd,((mtifInfo*)p->info)->arg[XPACKET][XM_IFNAME]);
  }
  return 0;
}

int packet_close(void* t, void* msg, void* wparam, void* lparam)
{
  mtifPacket* p = (mtifPacket*)t;
  p->m.pfxMTIF[ONPACKETREAD] = 0;

  mtifPacketClose(&p->m, p->fd, ((MTIF*)p->pif)->mshm.p[0]);//p->b[0]);
  SYSTEM_LOG(0, 0, "Packet Close \r\n");
  return 0;
}

int packet_init(void* t, void* msg, void* wparam, void* lparam)
{
	int e = 0;
  mtifPacket* p = (mtifPacket*)t;
  p->info = wparam;

  p->m.key = "shinbaad@gmail.com";

  //memset(&p->m, 0, sizeof(XMTIFSHM));

  e = mtifPacketCreate(&p->m);
  if ( e<0 )
  {
    return -1;
  }

  SYSTEM_LOG(0, 0, "Packet Create Success[%d] \r\n", e);

  p->REG.COUNTER[0] = 0;

  xmsgq_set(t, MAKELONG(OPEN, XPACKET), wparam, lparam);
  return 0;
}

int packet_release(void* t, void* msg, void* wparam, void* lparam)
{
	int e = 0;
  mtifPacket* p = (mtifPacket*)t;

  p->m.pfxMTIF[ONPACKETREAD] = 0;

  e = mtifPacketDestroy(&p->m);
  if ( e<0 )
  {
    return -1;
  }

  SYSTEM_LOG(0, 0, "Packet Destroy Success[%d] \r\n", e);

  return 0;
}

int packet_idle(void* t, void* msg, void* wparam, void* lparam)
{
  mtifPacket* p = (mtifPacket*)t;
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

int packet_status(void* t, void* msg, void* wparam, void* lparam)
{
  switch(LOWORD((unsigned int)msg))
  {
    case INIT:
      packet_init(t, msg, wparam, lparam);
      break;
    case RELEASE:
      packet_release(t, msg, wparam, lparam);
      break;
    case OPEN:
      packet_open(t, msg, wparam, lparam);
      break;
    case CLOSE:
      packet_close(t, msg, wparam, lparam);
      break;
    case WRITE:
      packet_write(t, msg, wparam, lparam);
      break;
    case IDLE:
      packet_idle(t, msg, wparam, lparam);
      break;
      
  }
  return 0;
}

