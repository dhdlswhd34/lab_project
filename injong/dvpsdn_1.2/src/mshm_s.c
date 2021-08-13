#include <mcommon.h>
#include <mshm_s.h>

static mtifSHM_S* g;

int cxshm_s_read(void* t, void* msg, void* wparam, void* lparam)
{
  int e = 1;
  int i;
  mtifSHM_S* p = (mtifSHM_S*)t;

  e = mtifSHMRead(&p->m, p->rbuf,32, 0, 'B'); 
  if ( e<0 )
  {
    return -1;
  }
  
  printf("mtifSHM_S_Read:  e : %d (%08X) \r\n", e, e);

	for ( i=0 ; i<26 ; i++ )
	{
		printf(" rbuf[%2d] : %c \r\n", i, (p->rbuf[i]));
	}

	return 0;
}

int cxshm_s_write(void* t, void* msg, void* wparam, void* lparam)
{
  int e = 1;
  int i;
  mtifSHM_S* p = (mtifSHM_S*)t;
  
  for ( i=0 ; i<26 ; i++ )
	{
		(p->buf[i]) = 'A' + i;
	}

  e = mtifSHMWrite(&p->m, p->buf,26,0, 'B'); 
  
  if ( e<0 )
  {
    return -1;
  }
  
  printf("mtifSHM_SWrite:  e : %d (%08X) \r\n", e, e);

  if ( e<0 )
  {
    return -1;
  }
 
	return 0;
}

int cxshm_s_open(void* t, void* msg, void* wparam, void* lparam)
{
	int e = 1;
  mtifSHM_S* p = (mtifSHM_S*)t;


  SYSTEM_LOG(0, 0, "mtifSHM_S_Open %s %s %s [%d]\r\n",
									((mtifInfo*)p->info)->arg[XSHM_S][XM_KEY],
									((mtifInfo*)p->info)->arg[XSHM_S][XM_SIZE],
									((mtifInfo*)p->info)->arg[XSHM_S][XM_COUNT],e);


	//// "1024KB", "1024MB", "128MB", "2GB", "3TB"
	////  "1024", "KB"
	////   1024,  1024
	////   1024 *1024
	////  "1024", "MB"
	////   1024,  1024*1024
	////   1024 * (1024*1024)
	//// ((mtifInfo*)p->info)->arg[XSHM][XM_SIZE];

	p->sz = atoi(((mtifInfo*)p->info)->arg[XSHM_S][XM_SIZE]);
  p->cnt = atoi(((mtifInfo*)p->info)->arg[XSHM_S][XM_COUNT]);
  p->q = 0;
  e = mtifSHMOpen(&p->m, p->key, p->sz*p->cnt, 'B'); 

  if ( e<0 )
  {
    printf("mtifSHM_S:  e : %d (%08X) %d\r\n", e, e ,p->cnt);
    return -1;
  }


	p->p = mtifSHMGet(&p->m, 0);
  

  #if 0
  {
    int i=0;
    for ( i=0 ; i<10 ; i++ )
      {
      (p->buf[i]) = 'A' + i;
    }

    e = mtifSHMWrite(&p->m, p->buf,26,0, 'B'); 
    
    if ( e<0 )
    {
      return -1;
    }
    printf("mtifSHMWrite:  e : %d (%08X) \r\n", e, e);

    
  }
  #endif



  #if 0
  {
    int i;

    for ( i=0 ; i<26 ; i++ )
    {
      printf(" rbuf[%2d] : %c \r\n", i, *(p->p+i));
    }

  }
  #endif

  
  return 0;
}

int cxshm_s_close(void* t, void* msg, void* wparam, void* lparam)
{
  int e = 1;
  mtifSHM_S* p = (mtifSHM_S*)t;

  if ( e<0 )
  {
    return -1;
  }

  e = mtifSHMClose(&p->m);
  SYSTEM_LOG(0, 0, "SHM Close Success[%d] \r\n", e);
  return 0;
}

int cxshm_s_init(void* t, void* msg, void* wparam, void* lparam)
{
  mtifSHM_S* p = (mtifSHM_S*)t;
  g = p;
  memset(&p->m, 0, sizeof(XMTIFSHM));
  p->info = wparam;
  SYSTEM_LOG(0, 0, "SHM_S init \r\n");
  xmsgq_set(t, MAKELONG(OPEN, XSHM_S), wparam, lparam);
  return 0;
}

int cxshm_s_release(void* t, void* msg, void* wparam, void* lparam)
{
	int e = 0;
  return 0;
}

int cxshm_s_status(void* t, void* msg, void* wparam, void* lparam)
{
  switch(LOWORD((unsigned int)msg))
  {
    case INIT:
      cxshm_s_init(t, msg, wparam, lparam);
      break;
    case RELEASE:
      cxshm_s_release(t, msg, wparam, lparam);
      break;
    case OPEN:
      cxshm_s_open(t, msg, wparam, lparam);
      break;
    case CLOSE:
      cxshm_s_close(t, msg, wparam, lparam);
      break;
    case WRITE:
      //cxshm_s_write(t, msg, wparam, lparam);
      break;
    case IDLE:
      //xshm_s_idle(t, msg, wparam, lparam);
      break;
  }
  return 0;
}

