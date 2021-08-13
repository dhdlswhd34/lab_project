#include <mcommon.h>
#include <mwebsocket.h>

int readNlSock(int sockFd, char *bufPtr, int seqNum, int pId)
{
	struct nlmsghdr *nlHdr;
	int readLen = 0, msgLen = 0;
	do
	{
		/* Recieve response from the kernel */
		if((readLen = recv(sockFd, bufPtr, BUFSIZE - msgLen, 0)) < 0)
		{
			perror("SOCK READ: ");
			return -1;
		}

		nlHdr = (struct nlmsghdr *)bufPtr;

		/* Check if the header is valid */
		if((NLMSG_OK(nlHdr, readLen) == 0) || (nlHdr->nlmsg_type == NLMSG_ERROR))
		{
			perror("Error in recieved packet");
			return -1;
		}

		/* Check if the its the last message */
		if(nlHdr->nlmsg_type == NLMSG_DONE) 
		{
			break;
		}
		else
		{
			/* Else move the pointer to buffer appropriately */
			bufPtr += readLen;
      msgLen += readLen;
		}

		/* Check if its a multi part message */
		if((nlHdr->nlmsg_flags & NLM_F_MULTI) == 0) 
		{
			/* return if its not */
			break;
		}	
	} while((nlHdr->nlmsg_seq != seqNum) || (nlHdr->nlmsg_pid != pId));

	return msgLen;
}

/* parse the route info returned */
void parseRoutes(struct nlmsghdr *nlHdr, struct route_info *rtInfo)
{
	struct rtmsg *rtMsg;
	struct rtattr *rtAttr;
	int rtLen;

	rtMsg = (struct rtmsg *)NLMSG_DATA(nlHdr);

	/* If the route is not for AF_INET or does not belong to main routing table	then return. */
	if((rtMsg->rtm_family != AF_INET) || (rtMsg->rtm_table != RT_TABLE_MAIN))
		return;

	/* get the rtattr field */
	rtAttr = (struct rtattr *)RTM_RTA(rtMsg);
	rtLen = RTM_PAYLOAD(nlHdr);

	for(;RTA_OK(rtAttr,rtLen);rtAttr = RTA_NEXT(rtAttr,rtLen))
	{
		switch(rtAttr->rta_type) 
		{
			case RTA_OIF:
        if_indextoname(*(int *)RTA_DATA(rtAttr), rtInfo->ifName);
        break;
      case RTA_GATEWAY:
			memcpy(&rtInfo->gateWay, RTA_DATA(rtAttr), sizeof(rtInfo->gateWay));
			break;
			case RTA_PREFSRC:
      memcpy(&rtInfo->srcAddr, RTA_DATA(rtAttr), sizeof(rtInfo->srcAddr));
			break;
			case RTA_DST:
			memcpy(&rtInfo->dstAddr, RTA_DATA(rtAttr), sizeof(rtInfo->dstAddr));
      break;
		}
	}

	return;
}

// meat
int get_gatewayip(char *gatewayip, socklen_t size)
{
	int found_gatewayip = 0;
	struct nlmsghdr *nlMsg;
	struct rtmsg *rtMsg;
	struct route_info *rtInfo;
	char msgBuf[BUFSIZE]; // pretty large buffer
	int sock, len, msgSeq = 0;

	/* Create Socket */
	if((sock = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE)) < 0)
	{
		perror("Socket Creation: ");
		return(-1);
	}

	/* Initialize the buffer */
	memset(msgBuf, 0, BUFSIZE);

	/* point the header and the msg structure pointers into the buffer */
	nlMsg = (struct nlmsghdr *)msgBuf;
	rtMsg = (struct rtmsg *)NLMSG_DATA(nlMsg);

	/* Fill in the nlmsg header*/
	nlMsg->nlmsg_len = NLMSG_LENGTH(sizeof(struct rtmsg)); // Length of message.
	nlMsg->nlmsg_type = RTM_GETROUTE; // Get the routes from kernel routing table .
	nlMsg->nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST; // The message is a request for dump.
	nlMsg->nlmsg_seq = msgSeq++; // Sequence of the message packet.
	nlMsg->nlmsg_pid = getpid(); // PID of process sending the request.

	/* Send the request */
	if(send(sock, nlMsg, nlMsg->nlmsg_len, 0) < 0)
	{
		fprintf(stderr, "Write To Socket Failed...\n");
		return -1;
	}

	/* Read the response */
	if((len = readNlSock(sock, msgBuf, msgSeq, getpid())) < 0) 
	{
		fprintf(stderr, "Read From Socket Failed...\n");
		return -1;
	}

	/* Parse and print the response */
	rtInfo = (struct route_info *)malloc(sizeof(struct route_info));

	for(;NLMSG_OK(nlMsg,len);nlMsg = NLMSG_NEXT(nlMsg,len))
	{
		memset(rtInfo, 0, sizeof(struct route_info));
		parseRoutes(nlMsg, rtInfo);

		// Check if default gateway
		if (strstr((char *)inet_ntoa(rtInfo->dstAddr), "0.0.0.0"))
		{
			// copy it over
			inet_ntop(AF_INET, &rtInfo->gateWay, gatewayip, size);
			found_gatewayip = 1;
			break;
		}
	}

  free(rtInfo);
	close(sock);

	return found_gatewayip;
}



int getSwitchInfo(void* t)
{
  mtifWebSocket* p = (mtifWebSocket*)t;

  int s,i;
  char ipstr[100] = {0,};
  char macstr[40] = {0,};
  char subnstr[40] = {0,};
  char gtwstr[40] = {0,};  
  char fv_str[40] = "yhdb";
  struct ifreq ifr;
  struct ifconf ifc;
  struct sockaddr_in *sin;
  struct sockaddr *sa;

  s = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
  strncpy(ifr.ifr_name, "enp3s0", IFNAMSIZ);

  if (!(ioctl(s, SIOCGIFADDR, &ifr) < 0)) 
  {
    sin = (struct sockaddr_in *)&ifr.ifr_addr;
    strcpy(ipstr,inet_ntoa(sin->sin_addr));    
    //inet_ntop(AF_INET, ifr.ifr_addr.sa_data+2,ipstr,sizeof(struct sockaddr));
  }
  
  if(!(ioctl(s, SIOCGIFHWADDR, &ifr) < 0))
  {
    sa = &ifr.ifr_hwaddr;
    strcpy(macstr,ether_ntoa((struct ether_addr *)sa->sa_data));     
    //memcpy(macstr, ifr.ifr_hwaddr.sa_data, 6);
  }
  
  if ( !(ioctl(s, SIOCGIFNETMASK, &ifr) < 0) )    
	{
    sin = (struct sockaddr_in *)&ifr.ifr_addr;
    strcpy(subnstr,inet_ntoa(sin->sin_addr));  
	}
  close(s);

  get_gatewayip(gtwstr,20);

  for(i  = 0 ; i <  99 ; i++)
  {
     if(i < 17)
      p->cb[0x7+i] =  macstr[i];
     else if( 17 < i && i < 25)
      p->cb[0x7+i] =  fv_str[i-18];
     else if( 25 < i && i < 27);
      
     else if( 27 < i && i < 67)
      p->cb[0x7+i] =  ipstr[i-28];
     else if( 67 < i && i < 83)
      p->cb[0x7+i] =  subnstr[i-68];
     else if( 83 < i && i < 99)
      p->cb[0x7+i] =  gtwstr[i-84];
     else
      p->cb[7+i] = JUMP;
  } 
  
  //strncat(p->cb,macstr,17);  //mac
  //strcat(p->cb,jump);   
  //strncat(p->cb,ipstr,39);  //ip
  return i;
}

int getSetTime(void* t)
{
  int i;
  mtifWebSocket* p = (mtifWebSocket*)t;
  for(i = 0 ; i < 19; i++)
  {
    if( i < 10)
      p->cb[0x7+i] = 0; //data
    else if( 10 < i)
      p->cb[0x7+i] = 0; //time
    else
      p->cb[0x7+i] = JUMP; //time
  }
  return i;
}

int saveSetTime(void* t, char *b)
{
  int i;
  mtifWebSocket* p = (mtifWebSocket*)t;
  for(i = 0 ; i < 19; i++)
  {
    if( i < 10)
      p->cb[0x7+i] = b[0x7+i]; //data
    else if( 10 < i)
      p->cb[0x7+i] = b[0x7+i]; //time
    else
      p->cb[0x7+i] = JUMP; //time
  }
  return i;
}

int getFirmware(void * t)
{
  char ver[20]  = "1.00.1";
  mtifWebSocket* p = (mtifWebSocket*)t;
  strcat(p->cb,ver);
  return strlen(ver);
}

int getPortStatus(void * t)
{
  mtifWebSocket* p = (mtifWebSocket*)t;
  strncat(p->cb,p->portb,3);
  return strlen(p->portb);
}

void savePortStatus(void* o ,char* b)
{
  //mtifWebSocket* p = (mtifWebSocket*)t;
}

int getOpenFlowInformation(void* o)
{
  int i;
  mtifWebSocket* p = (mtifWebSocket*)o;
  for(i = 0 ; i < 47; i++)
  {
    if(i< 1)
    p->cb[0x7+i] = '0';
    else if( 1 < i && i < 36)
      ;
    else if( 36 < i && i < 41)
      ;
    else if( 41 < i && i < 43)
      p->cb[0x7+i] = '0';
    else if( 43 < i && i < 45)  
      p->cb[0x7+i] = '1';
    else
      p->cb[0x7+i] = JUMP;
  }

  return i;
}

int SaveOpenFlowInformation(void * o)
{
  int i;
  mtifWebSocket* p = (mtifWebSocket*)o;
  for(i = 0 ; i < 47; i++)
  {
    if(i< 1)
      p->cb[0x7+i] = '0';
    else if( 1 < i && i < 36)
      ;
    else if( 36 < i && i < 41)
      ;
    else if( 41 < i && i < 43)
      p->cb[0x7+i] = '0';
    else if( 43 < i && i < 45)  
      p->cb[0x7+i] = '1';
    else
      p->cb[0x7+i] = JUMP;
  }
  return i;
}


void* on_websocket_readex_check(void* t,void* fd,char* b,int sz,void* mi, int arg1,void* o)
{
  mtifWebSocket* p = (mtifWebSocket*)o;
  int s;


  int i=0;
  int j = 0;
  for ( i=0 ; i < sz ; i++ )
  {
    if ( p->REG.SR == 0x00 )
    {
      if ( (*(b+i)==0x02) ) //START
      {
        p->REG.SR |= 0x80;
        p->cpos = 0;
        p->cb[p->cpos++] = *(b+i);
      }
      //1~9//
      if((i == 4))
      {
        p->cb[p->cpos++] = '1';
        p->cb[p->cpos++] = '0';
        p->cb[p->cpos++] = '0';
        p->cb[p->cpos++] = *(b+i);
        if(*(b+i) == '0')
        {
          switch(*(b+i+1))
          {
            case '1': 
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              p->cpos += getSwitchInfo(o);
              printf("getSwitchInfo\n");
              break;
            case '2':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("saveSwitchInfo\n");
              break;
            case '3':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              p->cpos += getSetTime(o);
              printf("getSetTime\n");
              break;
            case '4':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              p->cpos += saveSetTime(o,b);
              printf("saveSetTime\n");
              break;
            case '5':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              p->cpos += getFirmware(o);  
              printf("getFirmware\n");
              break;
            case '6':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("uploadFirmware\n");
              break;
            case '7':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              p->cpos += getPortStatus(o);  
              printf("getPortStatus\n");
              break;
            case '8':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              savePortStatus(o,b);
              printf("savePortStatus\n");
              break;
            case '9':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              
              printf("getAllInfoList\n");
              break;
            default :
              break;
          }
        }
        //10~19//
        else if(*(b+i) == '1')
        {
          switch(*(b+i+1))
          {
            case '0':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("rebootSystem \n");
              break;
            case '1':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("savePassword \n");
              break;
            case '2':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("resetPassword \n");
              break;
            case '3':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              p->cb[p->cpos++] = '0';
              printf("getSEEDInformation \n");
              break;
            case '4':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("saveSEEDInformation \n");
              break;
            case '5':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              p->cb[p->cpos++] = '0';
              printf("getARIAInformation \n");
              break;
            case '6':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("saveARIAInformation \n");
              break;
            case '7':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              p->cb[p->cpos++] = '0';
              printf("getLEAInformation \n");
              break;
            case '8':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("saveLEAInformation \n");
              break;
            case '9':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              p->cb[p->cpos++] = '0';  
              printf("getHIGHTInformation \n");
              break;
            default :
              break;
          }
        }
        //20~28//
        else if(*(b+i) == '2')
        {
          switch(*(b+i+1))
          {
            case '0':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("saveHIGHTInformatio \n");
              break;
            case '1':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              p->cb[p->cpos++] = '0';  
              printf("getHMACInformation \n");
              break;
            case '2':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("saveHMACInformation \n");
              break;
            case '3':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              p->cb[p->cpos++] = '0';
              printf("getSHA256Information \n");
              break;
            case '4':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("saveSHA256Information \n");
              break;
            case '5':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              p->cb[p->cpos++] = '0';
              printf("getLSHInformation \n");
              break;
            case '6':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("saveLSHInformatio \n");
              break;
            case '7':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              p->cb[p->cpos++] = '0';
              printf("getHASHDRBGInformation \n");
              break;
            case '8':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("saveHASHDRBGInformation \n");
              break;
            default :
              break;
          }
        }
        //29~37//
        else if(*(b+i) == '3')
        {
          switch(*(b+i+1))
          {
            case '0':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              p->cpos += getOpenFlowInformation(o);
              printf("getOpenFlowInformation \n");
              break;
            case '1':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              p->cpos += SaveOpenFlowInformation(o);
              printf("SaveOpenFlowInformation \n");
              break;
            case '2':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("getVirtualLanInformation \n");
              break;
            case '3':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("SaveVirtualLanInformation \n");
              break;
            case '4':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("getOepnFlowDtlInformation \n");
              break;
            case '5':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("getFlowInformation \n");
              break;
            case '6':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("getMetersInformation \n");
              break;
            case '7':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("getActivePortLists \n");
              break;
            case '8':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("getSecurityModeLists \n");
              break;
            default :
              break;
          }
        }
        //38~42//
        else if(*(b+i) == '4')
        {
          switch(*(b+i+1))
          {
            case '2':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("GetAnomalyPacketCount \n");
              break;
            case '3':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("resetFactorySwitchInformacti on\n");
              break;
            case '4':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("resetPortStatusInformation \n");
              break;
            case '5':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("getTodayRecivePacketsSts \n");
              break;
            case '6':
              p->cb[p->cpos++] = *(b+i+1);
              p->cb[p->cpos++] = 0x5E;
              printf("GetAnomalyPacketSts \n");
              break;
            default :
              break;
          }
        }
      }
      p->REG.SR |= 0x80;
    }
    else
    {
      if ( p->REG.SR == 0x80 )
      {
        if ( (p->cpos != 0) )
        {
          if ( (*(b+i)==0x03) ) //END
          {
            p->REG.SR |= 0x40;
            printf("--------%X---------\n",p->REG.SR);
          }
          else
          {
            //p->cpos = 0;
            p->REG.SR = 0;
          }
        }
      }
    }
    if ( (p->REG.SR&0xC0) == 0xC0 )
    {
      p->cb[p->cpos++] = *(b+i);
    }
  }
  p->cpos %= WS_MAX_BUF_SZ;

  return (void*)p->cpos;
}


int websocket_broadcast(void* t, void* msg, void* wparam, void* lparam)
{
  int e = 0;
  int i = 0;
  int s = 0;
  mtifWebSocket* p = (mtifWebSocket*)t;

  fprint_buffer("websocket_broadcast", (char*)lparam, (int)wparam, 0, 16);
  if ( ((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_CSTYPE][0] == 'S' )
  {
    s=mtifWebSocketClientSet(&p->m, (void**)&p->cs);
    for (i=0 ; i<s ; i++ )
    {
      if ( (p->cs+i)->fd > 0 )
      {
        e = mtifWebSocketWrite(&p->m, (p->cs+i)->fd, (char*)lparam,(int)wparam);
        if ( e > 0 ) SYSTEM_LOG(0, 0, "[%4d:%4d] %d\r\n", i, (p->cs+i)->fd, e);
      }
    }
  }
  return 0;
}


int websocket_write(void* t, void* msg, void* wparam, void* lparam)
{
  mtifWebSocket* p = (mtifWebSocket*)t;
  int e = 0;
  int fd = (int)wparam;
  int idx = (int)lparam;

  #if 1
  //mcsleep(1000000);
  display_buffer("p->cb", p->cb, p->rsp_sz);
  e = mtifWebSocketWriteEx(&p->m, fd, p->cb, p->rsp_sz, 0x01, 0, 1);
	printf("mtifWebSocketSendEx : %08X \r\n", e);
  memset(p->cb,0,sizeof(p->cb));
  display_buffer("clean", p->cb, p->rsp_sz);
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
  int idx = (mi==0)?0:(*(int*)mi);

  SYSTEM_LOG(0,0,"WebSocket status %d %d (%08X:%d) %08X\r\n",fd,idx, sz,sz, err);
 
  switch(err)
  {
    case 0xE000ACCB:
      if ( ((mtifInfo*)((mtifWebSocket*)o)->info)->arg[XWEBSOCKET][XM_CSTYPE][0]=='S' )
      {
        ((mtifWebSocket*)o)->pack.info[idx].fd = fd;
        ((mtifWebSocket*)o)->pack.info[idx].buf[0] = 0x80|WEBSOCKET_BUF_SFT;
        *((char**)b) = ((mtifWebSocket*)o)->pack.info[idx].buf;
        SYSTEM_LOG(0,0,"Client [%4d] Connected at %4d\r\n", fd, idx);
      
      }
      break;

    case 0xE000101F:
      if ( ((mtifInfo*)((mtifWebSocket*)o)->info)->arg[XWEBSOCKET][XM_CSTYPE][0]=='S' )
      {
        int e = 0;
        ((mtifWebSocket*)o)->pack.info[idx].fd = 0;
        ((mtifWebSocket*)o)->pack.info[idx].buf[0] = 0;
        SYSTEM_LOG(0,0,"Client [%4d] Disrconnected at %4d\r\n", fd, idx);
      }
      break;

    case 0xE000B0FF:
      *((char**)b) = ((mtifWebSocket*)o)->iobuf;
      break;

    case 0xE00010BF:
      //((mtifWebSocket*)o)->pack.info[idx].buf[0] = WEBSOCKET_BUF_SFT;
      //*((char**)b) = ((mtifWebSocket*)o)->pack.info[idx].buf;
      //e = 1;
      break;

  }

  return (void*)e;
}


void* on_websocket_read(void* t,int fd,unsigned char* b,int sz,void* mi,int err,void* o)
{
  mtifWebSocket* p = (mtifWebSocket*)o;
  int i ,e=0;
  int idx = (mi==0)?0:(*(int*)mi);

  if ( err < 0 ) return 0;

  SYSTEM_LOG(0, 0, " _read ------>    %08X:%08X \r\n", p, o);

  fprint_buffer("read", b, sz, 0, 16);
  e = (int)on_websocket_readex_check(t,fd, b, sz, mi, err, o);
  p->rsp_sz = e;
  

  if ( (p->REG.SR&0xFF )== 0xC0 )
  {
    p->REG.SR = 0x00;
    p->cpos = 0;
    //SYSTEM_LOG(0, 0, "on_websocket_read -> p->cb %p\r\n", p->cb);
    //display_buffer("rcvd protocol", p->cb, e);
    fprint_buffer("After_Write", p->cb, e, 0, 16);
    xmsgq_set(t, MAKELONG(WRITE, XWEBSOCKET), (void*)fd, (void*)idx);
  }

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


  SYSTEM_LOG(0, 0, " _open ------>    %08X:%08X \r\n", &p->m, p);

  p->fd = mtifWebSocketOpen(&p->m,host,((mtifInfo*)p->info)->arg[XWEBSOCKET][XM_CSTYPE],0,p->pb,0,p);
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
  mtifWebSocketClose(&p->m, p->pb);
  p->m.pfxMTIF[ONWSSTATUS] = 0;
  p->m.pfxMTIF[ONWSREAD]   = 0;

  return 0;
}


int websocket_init(void* t, void* msg, void* wparam, void* lparam)
{
	int e = 0;
  char host[128];
  mtifWebSocket* p = (mtifWebSocket*)t;

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
  mtifWebSocket* p = (mtifWebSocket*)t;
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

