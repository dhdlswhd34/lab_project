#include <mcommon.h>
#include <mpacket.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHMSZ 1024
 
static mtifPacket* g;
PACKET_HEADER H[100];
void* SHM_ptr;

 void shared_Memory_S(unsigned char* b)
 {
    char c;
    int shmid;
    key_t key;
    int* shm,*s;

    key = 9778;


    if((shmid = shmget(key,SHMSZ,IPC_CREAT|0666))<0)
    {
      perror("shmget failed : ");

      exit(1);

    }
 
  if((shm = shmat(shmid,NULL,0))== (int*)-1)
    {
      perror("shmat failed : ");

      exit(1);

    }
 

  // shmid = shmget((key_t)3836, sizeof(SHM_INFOS)*100, 0666|IPC_CREAT);
  
  int i;
  for(i=0; i< 54 ; i++)
  { 
    *shm++ = *(b+i);
  }
  printf("Shared_Memory_write \r\n");
    
  //exit(0);
 }


 unsigned char* SHM_open(mtifPacket* shm)
 {
    int shmid;
    key_t key;
    int i;
    key = 9778;
    

    if((shmid = shmget(key,SHMSZ,IPC_CREAT|0666))<0)
    {
      perror("shmget failed : ");

      exit(1);

    }
 
  if((shm->shmp[0] = shmat(shmid,NULL,0))== (int*)-1)
    {
      perror("shmat failed : ");

      exit(1);

    }

  /*
  for(i=0; i< 54 ; i++)
  { 
    *shm++ = 'A';
  }
  */
  // shmid = shmget((key_t)3836, sizeof(SHM_INFOS)*100, 0666|IPC_CREAT);
   SYSTEM_LOG(0, 0, "%08d SHM_read %d \r\n", shmid, shm);
    
  //exit(0);
  return shm->shmp;
 }



int packet_SAVE(unsigned char* b,int count,int sz)
{
  
  FILE *pfile = NULL;
	int  j;
	char filename[100];
	FILE *fp;
  printf("--->>>%d",count);

	sprintf(filename, "/usr/local/dvl/project/trs/woong/Packet/PACKET%d", count);

	fp = fopen(filename, "w+");

	for (j = 0; j < sz; j++) 
  {
    fprintf(fp, "%02X ", *(b+j));      
    
  }
  printf("Save_Complete! \r\n");
  fclose(fp);

  return ++count;
}


void hex_to_decNum(PACKET_HEADER* H,int sz, int i)
{
  
  //fprint_buffer("on_packet_read",H+sz, 16, 0, 16); 
  if(i == 0)
  { 
   (H+sz)->temp += 0x100 * (((H+sz)->div_b[i]));
   //(H+sz)->div_b[i] = temp;
   //printf("--=---(*%x)----", ((H+sz)->div_b[i]));
   //printf("--=---*%x*----",(H+sz)->temp);
  }   
  else
  (H+sz)->temp +=(((H+sz)->div_b[i]));
  //printf("---*%02d*----",(H+sz)->temp);
  //return (H+sz)->temp;
}

int byte_to_bit(int byte)
{
  int f;
  if(byte == 0)
  {
    return byte;
  }
  while((byte / 0x10) != 0)
  {
    byte -= 0x10;
    f++;
  }
  printf("IPv%d ", f);
  return byte;

}




 void packet_div_arr(unsigned char* b, PACKET_HEADER* target, int sz,int start, int end)
{
  int i = 0;

  memcpy((H[sz].div_b) , b , (end-start));

  for( ; start < end; start++ )
  {
    if(sz == MAC_ADRESS_D)
    {
      printf("%02X:",H[sz].div_b[i]);
    }
    else if(sz == MAC_ADRESS_S)
    {
      printf("%02X:",H[sz].div_b[i]);
    }

    else if(sz == ETHER_TYPE)
    {
      printf("%02x",H[sz].div_b[i]);
    }

    else if(sz == IP_VER)
    {
      printf("%2dbyte", byte_to_bit(H[sz].div_b[i])*4  );
    }

    else if(sz == PROTOCAL)
    {
      printf("%02x",H[sz].div_b[i]);
    }

    else if(sz == IP_ADRESS_S)
    {
      printf("%d.",H[sz].div_b[i]);   
    }
   
    else if(sz == IP_ADRESS_D)
    {
      printf("%d.",H[sz].div_b[i]);   
    }
   
    else if(sz == PORT_S)
    {
        //char tmp;
        //hex_to_decNum(H,sz,i);
       
         printf("%02X",H[sz].div_b[i]);
    }
     
    else if(sz == PORT_D)
    {
      hex_to_decNum(H,sz,i);
      printf("%02d ",H[sz].temp);
        //printf("%02d",H[sz].div_b[i]);
        H[sz].temp=0;
    }

    else if(sz == DATA)
    {
        if(i ==0)
        {
          printf("\r\n");
          printf("|");
        }
        else if( !(i% 0x10) || (i == 0x36))
        {
          
          printf("|");
          printf("\r\n");
          printf("|");  
        }
        if( !(i % 0x08 ) ) printf("  ");
        printf("%02X ",H[sz].div_b[i]);
    }

    else
    {
      printf("%02X",H[sz].div_b[i]);
    }

    i++;
  }
  printf("\r\n");
}



void packet_div(unsigned char* b,PACKET_HEADER* target, int sz , int start, int end,char* name,char * sub_name)
{
  int i;

  H->cur = 0;

  b = ( b + start) ? b + start :  0; 
  if(b == 0)
  {
    return;
  }  
  printf("[%15s|",name);
  printf("%15s]",sub_name);
  packet_div_arr( b, H, sz, start,  end);   
  

}


int packet_write(void* t, void* msg, void* wparam, void* lparam)
{
  return 0;
}


void* on_packet_status(void* t,int fd,unsigned char* b,int sz,void* mi,int err,void* o)
{
  int e = 0;
  SYSTEM_LOG(0, 0, "on_packet_status %08X \r\n", err);

  if ( err == 0xE000001B )
  {

  }
  else if ( err == 0xE00010BF )
  {


    #if 0   /// usr' mem
    ((mtifPacket*)o)->qidx++;
    ((mtifPacket*)o)->qidx %= MAX_BUF_QUE;
    ((mtifPacket*)o)->b[((mtifPacket*)o)->qidx][0] = MAX_BUF_SZ;
    *((char**)b) = ((mtifPacket*)o)->b[((mtifPacket*)o)->qidx];
    SYSTEM_LOG(0, 0, "%08X -> %08X \r\n", ((mtifPacket*)o)->b[((mtifPacket*)o)->qidx-1], ((mtifPacket*)o)->b[((mtifPacket*)o)->qidx]);
    #endif

    #if 1 /// SHM

    //*(shm_ptr+2) = PACKET_BUF_SFT; 
    printf("--->\n");

    int shmid;
    key_t key;
    int i;
    key = 9778;
    unsigned char* shm_ptr;

    if((shmid = shmget(key,SHMSZ,IPC_CREAT|0666))<0)
    {
      perror("shmget failed : ");

      exit(1);

    }
 
  if((shm_ptr = shmat(shmid,NULL,0))== (int*)-1)
    {
      perror("shmat failed : ");

      exit(1);
    }

    strcpy((shm_ptr), ((mtifPacket*)o)->shmp, 16);
    //*(shm_ptr) = *(((mtifPacket*)o)->shmp+2);

    *((char**)b) = ((mtifPacket*)o)->shmp;
    fprint_buffer("on_packet_read",((mtifPacket*)o)->shmp, sz, 0, 16); 
    #endif
    e = 1;
  }
  else if ( err == 0xE000001A )
  {
  }
  return (void*)e;
}

void* on_packet_read(void* t,int fd,unsigned char* b,int sz,void* mi,int err,void* o)
{
 
  if ( err<0 )on_packet_status(t,fd,b,sz,mi,err,o);
  if ( sz <= 0 ) return 0;
 

  if((*(b+12) == 0x08) && (*(b+13) == 0x00))  //ip_ver4
  {
    //strncpy(SHM_open(((mtifPacket*)o)->shmp), ((mtifPacket*)o)->shmp, 54);
    //SHM_open(((mtifPacket*)o)->shmp);
    //memcpy(, ((mtifPacket*)o)->shmp, 54);

   /// write to shmk 
      
      
  }


   sleep(1);
  
  return 0;

  SYSTEM_LOG(0, 0, "%08X on_packet_read %d \r\n", b, fd);
  
  //fprint_buffer("on_packet_read",b, sz, 0, 16); 

  //return 0;
  if((*(b+12) == 0x08) && (*(b+13) == 0x00))  //ip_ver4
  //if((*(b) == 0x50) && (*(b+13) == 0x00))  //ip_ver4
  { 
  
  
  fprint_buffer("on_packet_read",b, sz, 0, 16); 
  bar;
  packet_div(b,H, MAC_ADRESS_D, 0, 6,"MAC_ADRESS","Destination");
  packet_div(b,H, MAC_ADRESS_S, 6, 12,"MAC_ADRESS","Source");
  packet_div(b,H, ETHER_TYPE, 12, 14,"ETHER_TYPE","IP");
  change_bar;
  packet_div(b,H, IP_VER, 14, 15,"IP_VER","HEADER_LENGTH");
  packet_div(b,H, TOS, 15, 16,"TOS","");  
  packet_div(b,H, IP_LENGTH, 16, 18,"IP_LENGTH","");  
  packet_div(b,H, PACKET_ID, 18, 20,"PACKET_ID","");  
  packet_div(b,H, IP_FLAG, 20, 22,"IP_FLAG","");  
  packet_div(b,H, TTL, 22, 23,"TTL","");  
  packet_div(b,H, PROTOCAL, 23, 24,"PROTOCAL","TCP");
  packet_div(b,H, IP_H_CHECKSUM, 24, 26,"IP_H_CHECKSUM","");
  packet_div(b,H, IP_ADRESS_S, 26, 30,"IP_ADRESS","Source");
  packet_div(b,H, IP_ADRESS_D, 30, 34,"IP_ADRESS","Destination");
  change_bar;
  packet_div(b,H, PORT_S, 34, 36,"PORT","Source");
  packet_div(b,H, PORT_D, 36, 38,"PORT","Destination");  
  packet_div(b,H, SEQUENCE_NUM, 38, 42,"SEQUENCE_NUM",""); 
  packet_div(b,H, ACKNOW_NUK, 42, 46,"ACKNOW_NUK",""); 
  packet_div(b,H, FLAG, 46, 48,"FLAG",""); 
  packet_div(b,H, WINDOW_SZ, 48, 50,"WINDOW_SIZE",""); 
  packet_div(b,H, TCP_CHECKSUM, 50, 52,"TCP_CHECKSUM",""); 
  packet_div(b,H, URGENT_P, 52, 54,"URGENT_P",""); 
  packet_div(b,H, DATA, 54, 102,"DATA",""); 
  bar;   
  
  if(count_name != 10)
  {
    count_name = packet_SAVE(b,count_name,sz);
    shared_Memory_S(b);    
  }
	else
	{
		count_name = 0;
	}
  //fprint_buffer("on_packet_read",b+54, sz, 0, 16); 
  sleep(1);
  
  }
 
  return 0;
}


int packet_open(void* t, void* msg, void* wparam, void* lparam)
{
	int e = 0;
  int sz = MAX_BUF_SZ;
  mtifPacket* p = (mtifPacket*)t;
  SYSTEM_LOG(0, 0, "mtifPacketOpen %s %s\r\n",
              ((mtifInfo*)p->info)->arg[XPACKET][XM_IFNAME],
              ((mtifInfo*)p->info)->arg[XSOCKET][XM_DELAY_0]);
  p->m.pfxMTIF[ONPACKETREAD]   = on_packet_read;

  #if 0 // usr' mem
  p->b[0][0] = PACKET_BUF_SFT;       //pactket_size
  #endif

  #if 1 // SHM
  
  //*(shm_ptr+2) = PACKET_BUF_SFT;
  //p->shmp = shm_ptr+2 ; //

  p->shmp[0] = PACKET_BUF_SFT;
  p->qidx = 0;

  p->fd = mtifPacketOpen(&p->m,
              ((mtifInfo*)p->info)->arg[XPACKET][XM_IFNAME],
              #if 0 // usr' mem
              p->b[0],
              #endif
              #if 1 // SHM
              p->shmp,
              #endif
              p);
  #endif
 
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

  mtifPacketClose(&p->m, p->fd, p->b[0]);
  SYSTEM_LOG(0, 0, "Packet Close \r\n");
  return 0;
}

int packet_init(void* t, void* msg, void* wparam, void* lparam)
{
	int e = 0;
  mtifPacket* p = (mtifPacket*)t;
  g = p;
  p->info = wparam;

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

