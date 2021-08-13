#include <mcommon.h>
#include <mshm.h>

static mtifSHM* g;

int mshm_read(void* t, void* msg, void* wparam, void* lparam)
{
  int e = 1;
  int i;
  mtifSHM* p = (mtifSHM*)t;

  e = mtifSHMRead(&p->m, p->rbuf, 1024, 0, 'B'); 
  if ( e<0 )
  {
    return -1;
  }
  
  printf("mtifSHMRead:  e : %d (%08X) \r\n", e, e);

	for ( i=0 ; i<26 ; i++ )
	{
		printf(" rbuf[%2d] : %c \r\n", i, (p->rbuf[i]));
	}

	return 0;
}

int mshm_write(void* t, void* msg, void* wparam, void* lparam)
{
  int e = 1;
  int i;
  mtifSHM* p = (mtifSHM*)t;
  
  for ( i=0 ; i<26 ; i++ )
	{
		(p->buf[i]) = 'A' + i;
	}

  e = mtifSHMWrite(&p->m, 
 p->buf,26,0, 'B'); 
  
  if ( e<0 )
  {
    return -1;
  }
  
  printf("mtifSHMWrite:  e : %d (%08X) \r\n", e, e);

  if ( e<0 )
  {
    return -1;
  }
 
	return 0;
}

int mshm_open(void* t, void* msg, void* wparam, void* lparam)
{
	int e = 1;
  mtifSHM* p = (mtifSHM*)t;


  SYSTEM_LOG(0, 0, "mtifSHMOpen %s %s %s [%d]\r\n",
									((mtifInfo*)p->info)->arg[XSHM][XM_KEY],
									((mtifInfo*)p->info)->arg[XSHM][XM_SIZE],
									((mtifInfo*)p->info)->arg[XSHM][XM_COUNT],e);


	//// "1024KB", "1024MB", "128MB", "2GB", "3TB"
	////  "1024", "KB"
	////   1024,  1024
	////   1024 *1024
	////  "1024", "MB"
	////   1024,  1024*1024
	////   1024 * (1024*1024)
	//// ((mtifInfo*)p->info)->arg[XSHM][XM_SIZE];
	p->sz = atoi(((mtifInfo*)p->info)->arg[XSHM][XM_SIZE]);
  p->cnt = atoi(((mtifInfo*)p->info)->arg[XSHM][XM_COUNT]);


  e = mtifSHMOpen(&p->m, 7810, p->sz*p->cnt, 'B'); 
  
  if ( e<0 )
  {
    printf("mtifSHMWrite:  e : %d (%08X) \r\n", e, e);
    return -1;
  }


	p->p = mtifSHMGet(&p->m, 0);
  

  #if 0
  {
    int i=0;
    for ( i=0 ; i<26 ; i++ )
    {
      (p->buf[i]) = 'A' + i;
    }

    e = mtifSHMWrite(&p->n, p->buf,26,0, 'B'); 
    
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

int mshm_close(void* t, void* msg, void* wparam, void* lparam)
{
  int e = 1;
  mtifSHM* p = (mtifSHM*)t;

  if ( e<0 )
  {
    return -1;
  }

  e = mtifSHMClose(&p->m);
  SYSTEM_LOG(0, 0, "SHM Close Success[%d] \r\n", e);
  return 0;
}

int mshm_init(void* t, void* msg, void* wparam, void* lparam)
{
  mtifSHM* p = (mtifSHM*)t;
  g = p;
  memset(&p->m, 0, sizeof(XMTIFSHM));
  p->info = wparam;

  xmsgq_set(t, MAKELONG(OPEN, XSHM), wparam, lparam);
  return 0;
}

int mshm_release(void* t, void* msg, void* wparam, void* lparam)
{
	int e = 0;
  return 0;
}

int mshm_status(void* t, void* msg, void* wparam, void* lparam)
{
  switch(LOWORD((unsigned int)msg))
  {
    case INIT:
      mshm_init(t, msg, wparam, lparam);
      break;
    case RELEASE:
      mshm_release(t, msg, wparam, lparam);
      break;
    case OPEN:
      mshm_open(t, msg, wparam, lparam);
      break;
    case CLOSE:
      mshm_close(t, msg, wparam, lparam);
      break;
    case WRITE:
      //mshm_write(t, msg, wparam, lparam);
      break;
    case IDLE:
      //xshm_idle(t, msg, wparam, lparam);
      break;
  }
  return 0;
}

