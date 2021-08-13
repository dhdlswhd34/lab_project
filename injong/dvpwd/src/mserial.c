#include <mcommon.h>
#include <mserial.h>
int string2hex(char* s, int sz, unsigned char* o)
{
  int idx = 0;
  int i = 0;

  //for ( idx=0 ; idx<sz ; idx+=2 )
  //{
  //  *(o+i) = (unsigned char)hex_to_digit( (s+idx) );
  //  i++;
  //}
  //*(o+i) = 0;
  return i;
}


int string2hex_re(char* b)
{
  int e = 0;

  //if(p->re_ab < 32)
  //{       
  //  if(p->chk ==20)
  //  {
  //    e = string2hex(p->re, 20, p->cbuf); 
  //    display_buffer("serial convert", p->cbuf, e);
  //    SYSTEM_LOG(0, 0, "->crc ---%X\r\n",*((p->cbuf)+7));
  //    set_init();
  //  }
  //  
  //  p->re[p->re_ab] = b[0];
  //  
  //  if(start_chk(p->re,p->chk))
  //  {
  //    p->chk   += 1;
  //    p->re_ab += 1;
  //  }
  //  else if(start_chk(p->re,p->chk))
  //  {
  //   set_init();
  //  }

  //  if(end_chk(p->re,p->re_ab))
  //  {
  //    set_init();
  //  }
  //}  
  return e; 
}


void set_init()
{
  //p->re_ab = 0;
  //p->chk = 0;  
}

int end_chk(char* re,int* re_ab)
{
  //if(re_ab == 20)
  //  {
  //    if(re[17] != 'F' || re[16] != 'F')
  //    {  
  //     return 1;
  //    }
  //        
  //    else return 0;
  //  }
  return 0;
}

int start_chk(char* re,int* chk)
{
  int e = 0;
  //if(*(re) == 'F') 
  //{    
  //     
  //  if( chk == 1)  
  //  {    
  //    if(*(re+1) == 'E') 
  //    {    
  //      e = 1;
  //    }
  //    else
  //    {
  //      e = 0;
  //    }
  //  }
  //  else
  //  {
  //    e = 1;
  //  }
  //}
  //else
  //{
  //  e = 0;
  //}
   
  return e;
}



void* on_serial_readex_check_ASCII(void* t,void* fd,char* b,int sz,void* mi, int arg1,void* o)
{
  mtifSerial* p = (mtifSerial*)o;

  int i=0;
  for ( i=0 ; i<sz ; i++ )
  {
    if ( p->REG.SR == 0x00 )
    {
      if ( (*(b+i)=='F') )
      {
        p->REG.SR |= 0x80;
        p->cpos = 0;
        p->cb[p->cpos++] = *(b+i);
      }
    }
    else
    if ( p->REG.SR == 0x80 )
    {
      if ( (p->cpos==1) )
      {
        if ( (*(b+i)=='E') )
        {
          p->REG.SR |= 0x40;
        }
        else
        {
          p->cpos = 0;
          p->REG.SR = 0;
        }
      }
    }

    if ( (p->REG.SR&0xC0) == 0xC0 )
    {
      p->cb[p->cpos++] = *(b+i);
    }

    if ( (p->cpos==17) && (*(b+i)=='F') ) p->REG.SR |= 0x08;
    if ( (p->cpos==18) && (*(b+i)=='F') ) p->REG.SR |= 0x04;
  }
  p->cpos %= MAX_MSERIAL_BUF_COUNT;
  
  return (void*)p->cpos;
}

#if 0


int on_serial_read_check(void* t,void* fd,char* b,int sz,int arg1,void* o)
{
  int i=0;
  for ( i=0 ; i<sz ; i++ )
  {
    if ( *(b+i) == 0xFE )
    {
      p->cpos = 0;
      p->REG.SR |= 0x80;
    }

    if ( p->REG.SR&0x80 )
    {
      p->cbuf[p->cpos++] = *(b+i);
    }

    if ( (p->REG.SR&0x80) && (*(b+i)==0xFF) )
    {
      p->REG.SR |= 0x01;
    }
  }

  p->cpos %= MAX_MSERIAL_BUF_COUNT;
  
  return p->cpos;
}

int on_serial_reprotocol(void* t,char* b,int sz)
{
  int i=0;
  int j=0;
  for ( i=0,j=0 ;i<sz ; i++,j++ )
  {
    p->cbuf[j] = *(b+i);
    if ( i==0)
    {
      j++;
      p->cbuf[j] = 0x2B;
    }
  }
  return j;
}
#endif

static void* on_serial_status(void* t,void* fd,unsigned char* b,int sz,void* mi,int err,void* o)
{
  int e = 0;
  mtifSerial* p = (mtifSerial*)o;
  //SYSTEM_LOG(0,0, "fd : %4d, sz : %8d, %08X \r\n", (int)fd, sz, err);
  switch(err)
  {
    case 0xE000001B:
      break;

    case 0xE000001A:
      //*(char**)b = p->b[(++p->idx)%MAX_MSERIAL_BUF_COUNT];
      break;

    case 0xE00010BF:
      *(char**)b = p->b[(++p->idx)%MAX_MSERIAL_BUF_COUNT];
      e = 1;
      break;
  }
  return (void*)e;
}


static void* on_serial_read(void* t,void* fd,unsigned char* b,int sz,void* mi,int err,void* o)
{
  int e = 0;
  mtifSerial* p = (mtifSerial*)o;
  if ( err<0 )
  {
    return (void*)on_serial_status(t,fd,b,sz,mi,err,o);
  }
  SYSTEM_LOG(0,0, "fd : %4d, sz : %8d, %08X -> %s \r\n", (int)fd, sz, err, (char*)b);
  fprint_buffer("on_serial_read", (char*)b, (int)sz, 0, 16);
  //*((unsigned char**)b) = p->pbuf[(p->idx++)%MAX_MSERIAL_BUF_COUNT];
  
  if ( sz > 0 )
  {

    if( ((mtifInfo*)p->info)->arg[XSERIAL][XM_ECHOMODE][0] == '1' )
    {
      SYSTEM_LOG(0,0, "-> %p  -> %p  <- \r\n", b,  p->b[p->idx]);
      xmsgq_set(o, MAKELONG(WRITE, XSERIAL), (void*)sz, (void*)p->b[p->idx]);
    }

    #if NORMAL_MODE
    if( ((mtifInfo*)p->info)->arg[XSOCKET][XM_ENABLE][0] == 'E' )
    {
      SYSTEM_LOG(0,0, "msgq_set to XSOCKET \r\n");
      xmsgq_set(o, MAKELONG(BROADCAST, XSOCKET),    (void*)sz, (void*)b);
    }
    if( ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_ENABLE][0] == 'E' )
    {
      SYSTEM_LOG(0,0, "msgq_set to XWEBSOCKET \r\n");
      xmsgq_set(o, MAKELONG(BROADCAST, XWEBSOCKET), (void*)sz, (void*)b);
    }
    #endif

    #if ASCII_MODE 
    e = (int)on_serial_readex_check_ASCII(t,fd, b, sz, mi, err, o);
    //SYSTEM_LOG(0, 0, "p->cpos %d\r\n", p->cpos);
    //display_buffer("serial readex", p->cbuf, e);
    if ( (p->REG.SR&0xFF)==0xCC )
    {
      p->REG.SR = 0x00;
      //display_buffer("serial readex after", p->cbuf, e);
      //SYSTEM_LOG(0, 0, "Serial Read %d, %d\r\n", sz, p->cpos);
      p->cpos = 0;
      e = str_to_hex(p->cbuf, e, 0, p->bbuf);
      display_buffer("serial bin buffer", p->bbuf, e);
      SYSTEM_LOG(0, 0, "COIL,B/U->[%02X]  CRC->[%02X]\r\n", p->bbuf[6], p->bbuf[7]);
      xmsgq_set(t, MAKELONG(WRITE, XWEBSOCKET), (void*)e, (void*)p->bbuf);
    }
    #endif

    #if HEX_MODE
    e = on_serial_readex_check(t,fd, b, sz, arg1, o);
    if ( p->cpos > 0 ) display_buffer("serial readex", p->cbuf, p->cpos);

    if ( (p->REG.SR&0x81) == 0x81 )
    {
      p->REG.SR = 0x00;
      e = on_serial_reprotocol(t,p->cbuf,p->cpos);
      display_buffer("serial readex after", p->cbuf, e);
      xmsgq_set(t, MAKELONG(WRITE, XWEBSOCKET), (void*)e, (void*)p->cbuf);
      SYSTEM_LOG(0, 0, "Serial Read %d, %d\r\n", sz, p->cpos);
      p->cpos = 0;
    }
    //mtifSerialSetBufPtr(&p->m,p->pbuf[(p->idx++)%MAX_MSERIAL_BUF_COUNT]);
    #endif
  }
  return 0;
}

int serial_write(void* t, void* msg, void* wparam, void* lparam)
{
  int i=0;
  int e = 0;

  SYSTEM_LOG(0,0, "-> %p  <- \r\n", lparam);
  fprint_buffer("serial_write", (char*)lparam, (int)wparam, 0, 16);
  e = mtifSerialWrite(&((mtifSerial*)t)->m, ((mtifSerial*)t)->fd, (unsigned char*)lparam, (int)wparam);
  SYSTEM_LOG(0, 0, "serial_write %d, %d\r\n", (int)wparam, e);
  

  /***
  for ( i=0 ; ; )
  {
    e = mtifSerialWriteEx(&p->m,p->fd,query[i], strlen(query[i]), 0);
    printf("%d -> %d write %s\r\n", i, e, query[i]);
    i = (i+1)%8;

    mcsleep(1000000);
  }
  ***/
  return 0;
}


int serial_open(void* t, void* msg, void* wparam, void* lparam)
{
  int e;
  int sz = 1;
  mtifSerial* p = (mtifSerial*)t;
  p->info = wparam;

  p->m.pfxMTIF[ONSERIALREAD] = on_serial_read;

  //memcpy(p->pbuf[0], &sz, sizeof(int));
  p->b[0][0]=1;//SERIAL_BUF_SFT;
  p->chk = 0;
  p->idx = 0;
  SYSTEM_LOG(0, 0, "Serial Open (%s, %s, %s, %s, %s) \r\n",
                    ((mtifInfo*)p->info)->arg[XSERIAL][XM_PORT],
                    ((mtifInfo*)p->info)->arg[XSERIAL][XM_BAUDRATE],
                    ((mtifInfo*)p->info)->arg[XSERIAL][XM_DATABIT],
                    ((mtifInfo*)p->info)->arg[XSERIAL][XM_STOPBIT],
                    ((mtifInfo*)p->info)->arg[XSERIAL][XM_PARITYBIT]);


  p->fd = mtifSerialOpen(&p->m,
                          ((mtifInfo*)p->info)->arg[XSERIAL][XM_PORT],
                          ((mtifInfo*)p->info)->arg[XSERIAL][XM_BAUDRATE],
                          ((mtifInfo*)p->info)->arg[XSERIAL][XM_DATABIT],
                          ((mtifInfo*)p->info)->arg[XSERIAL][XM_STOPBIT],
                          ((mtifInfo*)p->info)->arg[XSERIAL][XM_PARITYBIT],
                          "0",
                          p->b[0],
                          p);
  if ( p->fd <= 0 )
  {
    SYSTEM_LOG(0, 0, "Serial Open Fail \r\n");
    return -1;
  }
  SYSTEM_LOG(0, 0, "Serial Open Success %d\r\n",(int)p->fd);
  return 0;
}

int serial_close(void* t, void* msg, void* wparam, void* lparam)
{
  int e;
  mtifSerial* p = (mtifSerial*)t;

  p->idx = 0;
  mtifSerialClose(&p->m, p->fd, p->b[0]);
  if ( p->fd < 0 )
  {
    SYSTEM_LOG(0, 0, "Serial Close Fail\r\n");
    return -1;
  }
  SYSTEM_LOG(0, 0, "Serial Close Success\r\n");
  return 0;
}

int serial_init(void* t, void* msg, void* wparam, void* lparam)
{
  int e;

  ((mtifSerial*)t)->info = wparam;
  ((mtifSerial*)t)->m.key = "shinbaad@gmail.com";

  e = mtifSerialCreate(&((mtifSerial*)t)->m);
  if ( e < 0 )
  {
    SYSTEM_LOG(0, 0, "Serial Create Fail\r\n");
    return -1;
  }
  SYSTEM_LOG(0, 0, "Serial Create Success\r\n");

  xmsgq_set(t, MAKELONG(OPEN, XSERIAL), wparam, lparam);
  
  return 0;
}

int serial_release(void* t, void* msg, void* wparam, void* lparam)
{
  int e;

  e = mtifSerialDestroy(&((mtifSerial*)t)->m);
  if ( e < 0 )
  {
    return -1;
  }
  SYSTEM_LOG(0, 0, "Serial Destroy Success\r\n");
  
  return 0;
}

int serial_status(void* t, void* msg, void* wparam, void* lparam)
{
  switch(LOWORD((unsigned int)msg))
  {
    case INIT:
      serial_init(t, msg, wparam, lparam);
      break;
    case RELEASE:
      serial_release(t, msg, wparam, lparam);
      break;
    case OPEN:
      serial_open(t, msg, wparam, lparam);
      break;
    case CLOSE:
      serial_close(t, msg, wparam, lparam);
      break;
    case WRITE:
      serial_write(t, msg, wparam, lparam);
      break;
    case COMPLETE:
      //xmsgq_set(NEXT, SERIAL, WRITE, lparam);
      break;
  }
  return 0;
}

  
