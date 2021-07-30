#include <mcommon.h>
#include <mxml.h>

static mtifInfo* info;

//int on_xml_parse(void* t,int sd,char* b,int sz,char* arg0,int arg1,void* o)
int on_xml_parse(void* a,void* b,void* c,void* d)
{
  int e = 0;
  char out[512];
  char enable[4];
  mtifXML* p = (mtifXML*)d;
  //SYSTEM_LOG(0, 0, "%s %s\r\n", b, arg0);

  if ( strncmp((char*)c, "CONFIG", 6) == 0 )
  {
    mtifXMLGetAttr(&p->m, 0, "system", out);
    mtifXMLGetAttr(&p->m, 0, "enable", enable);
    SYSTEM_LOG(0, 0, "%s enable=\"%s\"\r\n", out, enable);
    if ( *enable=='1' && strncmp(out, "GPSM", strlen(out))==0 )
    {
      info->arg[GPSM][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "delay",     info->arg[GPSM][XM_DELAY_0]);
      mtifXMLGetAttr(&p->m, 0, "port",      info->arg[GPSM][XM_PORT]);
      mtifXMLGetAttr(&p->m, 0, "baudrate",  info->arg[GPSM][XM_BAUDRATE]);
      mtifXMLGetAttr(&p->m, 0, "databit",   info->arg[GPSM][XM_DATABIT]);
      mtifXMLGetAttr(&p->m, 0, "stopbit",   info->arg[GPSM][XM_STOPBIT]);
      mtifXMLGetAttr(&p->m, 0, "paritybit", info->arg[GPSM][XM_PARITYBIT]);
      mtifXMLGetAttr(&p->m, 0, "blockmode", info->arg[GPSM][XM_BLOCKMODE]);
    }
    else if ( *enable=='1' && strncmp(out, "WFM", strlen(out))==0 )
    {
      info->arg[XWFM][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "sdelay",    info->arg[XWFM][XM_DELAY_0]);
      mtifXMLGetAttr(&p->m, 0, "ldelay",    info->arg[XWFM][XM_DELAY_1]);
      mtifXMLGetAttr(&p->m, 0, "port",      info->arg[XWFM][XM_PORT]);
      mtifXMLGetAttr(&p->m, 0, "baudrate",  info->arg[XWFM][XM_BAUDRATE]);
      mtifXMLGetAttr(&p->m, 0, "databit",   info->arg[XWFM][XM_DATABIT]);
      mtifXMLGetAttr(&p->m, 0, "stopbit",   info->arg[XWFM][XM_STOPBIT]);
      mtifXMLGetAttr(&p->m, 0, "paritybit", info->arg[XWFM][XM_PARITYBIT]);
      mtifXMLGetAttr(&p->m, 0, "blockmode", info->arg[XWFM][XM_BLOCKMODE]);
      mtifXMLGetAttr(&p->m, 0, "ap_ssid",   info->arg[XWFM][XM_AP_SSID]);
      mtifXMLGetAttr(&p->m, 0, "ap_pw",     info->arg[XWFM][XM_AP_PW]);
      mtifXMLGetAttr(&p->m, 0, "est",       info->arg[XWFM][XM_EST]);
      mtifXMLGetAttr(&p->m, 0, "estid",     info->arg[XWFM][XM_ESTID]);
      mtifXMLGetAttr(&p->m, 0, "ept",       info->arg[XWFM][XM_EPT]);
      mtifXMLGetAttr(&p->m, 0, "esi",       info->arg[XWFM][XM_ESI]);
      mtifXMLGetAttr(&p->m, 0, "esp",       info->arg[XWFM][XM_ESP]);
    }
    else if ( *enable=='1' && strncmp(out, "SERIAL", strlen(out))==0 )
    {
      info->arg[XSERIAL][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "delay",     info->arg[XSERIAL][XM_DELAY_0]);
      mtifXMLGetAttr(&p->m, 0, "port",      info->arg[XSERIAL][XM_PORT]);
      mtifXMLGetAttr(&p->m, 0, "baudrate",  info->arg[XSERIAL][XM_BAUDRATE]);
      mtifXMLGetAttr(&p->m, 0, "databit",   info->arg[XSERIAL][XM_DATABIT]);
      mtifXMLGetAttr(&p->m, 0, "stopbit",   info->arg[XSERIAL][XM_STOPBIT]);
      mtifXMLGetAttr(&p->m, 0, "paritybit", info->arg[XSERIAL][XM_PARITYBIT]);
      mtifXMLGetAttr(&p->m, 0, "blockmode", info->arg[XSERIAL][XM_BLOCKMODE]);
      mtifXMLGetAttr(&p->m, 0, "echomode",  info->arg[XSERIAL][XM_ECHOMODE]);
      xmsgq_set(p, (void*)MAKELONG(INIT, XSERIAL), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "SERTEST", strlen(out))==0 )
    {
      info->arg[SERTEST][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "port",      info->arg[SERTEST][XM_PORT]);
      mtifXMLGetAttr(&p->m, 0, "baudrate",  info->arg[SERTEST][XM_BAUDRATE]);
      mtifXMLGetAttr(&p->m, 0, "databit",   info->arg[SERTEST][XM_DATABIT]);
      mtifXMLGetAttr(&p->m, 0, "stopbit",   info->arg[SERTEST][XM_STOPBIT]);
      mtifXMLGetAttr(&p->m, 0, "paritybit", info->arg[SERTEST][XM_PARITYBIT]);
      mtifXMLGetAttr(&p->m, 0, "blockmode", info->arg[SERTEST][XM_BLOCKMODE]);
      mtifXMLGetAttr(&p->m, 0, "delay",     info->arg[SERTEST][XM_DELAY_0]);
    }
    else if ( *enable=='1' && strncmp(out, "WEBSOCKET", strlen(out))==0 )
    {
      info->arg[XWEBSOCKET][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "delay",     info->arg[XWEBSOCKET][XM_DELAY_0]);
      mtifXMLGetAttr(&p->m, 0, "ip",        info->arg[XWEBSOCKET][XM_IP]);
      mtifXMLGetAttr(&p->m, 0, "port",      info->arg[XWEBSOCKET][XM_PORT]);
      mtifXMLGetAttr(&p->m, 0, "type",      info->arg[XWEBSOCKET][XM_CSTYPE]);
      mtifXMLGetAttr(&p->m, 0, "echomode",  info->arg[XWEBSOCKET][XM_ECHOMODE]);
      xmsgq_set(p, (void*)MAKELONG(INIT, XWEBSOCKET), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "WEBSOCKET_S", strlen(out))==0 )
    {
      info->arg[XWEBSOCKET_S][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "delay",   info->arg[XWEBSOCKET_S][XM_DELAY_0]);
      mtifXMLGetAttr(&p->m, 0, "ip",      info->arg[XWEBSOCKET_S][XM_IP]);
      mtifXMLGetAttr(&p->m, 0, "port",    info->arg[XWEBSOCKET_S][XM_PORT]);
      mtifXMLGetAttr(&p->m, 0, "type",    info->arg[XWEBSOCKET_S][XM_CSTYPE]);
      mtifXMLGetAttr(&p->m, 0, "echomode",info->arg[XWEBSOCKET_S][XM_ECHOMODE]);
      xmsgq_set(p, (void*)MAKELONG(INIT, XWEBSOCKET_S), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "PACKET", strlen(out))==0 )
    {
      info->arg[XPACKET][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "delay",     info->arg[XPACKET][XM_DELAY_0]);
      mtifXMLGetAttr(&p->m, 0, "ifname",    info->arg[XPACKET][XM_IFNAME]);
      xmsgq_set(p, (void*)MAKELONG(INIT, XPACKET), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "SOCKET", strlen(out))==0 )
    {
      info->arg[XSOCKET][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "delay",     info->arg[XSOCKET][XM_DELAY_0]);
      mtifXMLGetAttr(&p->m, 0, "ip",        info->arg[XSOCKET][XM_IP]);
      mtifXMLGetAttr(&p->m, 0, "port",      info->arg[XSOCKET][XM_PORT]);
      mtifXMLGetAttr(&p->m, 0, "protocol",  info->arg[XSOCKET][XM_PROTO]);
      mtifXMLGetAttr(&p->m, 0, "type",      info->arg[XSOCKET][XM_CSTYPE]);
      mtifXMLGetAttr(&p->m, 0, "cast",      info->arg[XSOCKET][XM_CASTTYPE]);
      mtifXMLGetAttr(&p->m, 0, "echomode",  info->arg[XSOCKET][XM_ECHOMODE]);
      xmsgq_set(p, (void*)MAKELONG(INIT, XSOCKET), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "HTTP", strlen(out))==0 )
    {
      info->arg[XHTTP][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "sdelay",    info->arg[XHTTP][XM_DELAY_0]);
      mtifXMLGetAttr(&p->m, 0, "ldelay",    info->arg[XHTTP][XM_DELAY_1]);
      mtifXMLGetAttr(&p->m, 0, "ip",        info->arg[XHTTP][XM_IP]);
      mtifXMLGetAttr(&p->m, 0, "port",      info->arg[XHTTP][XM_PORT]);
      mtifXMLGetAttr(&p->m, 0, "uri",       info->arg[XHTTP][XM_URI]);
      xmsgq_set(p, (void*)MAKELONG(INIT, XHTTP), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "SSL", strlen(out))==0 )
    {
      info->arg[XSSL][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "delay",     info->arg[XSSL][XM_DELAY_0]);
      mtifXMLGetAttr(&p->m, 0, "ip",        info->arg[XSSL][XM_IP]);
      mtifXMLGetAttr(&p->m, 0, "port",      info->arg[XSSL][XM_PORT]);
      mtifXMLGetAttr(&p->m, 0, "type",      info->arg[XSSL][XM_CSTYPE]);
    }
  }

  return e;
}


void* on_xml_startdocs(void* a,void* b,void* c,void* d)
{
  SYSTEM_LOG(0,0,"on_xml_startdocs : %s, %s \r\n", (char*)b, (char*)c);
  return 0;
}
void* on_xml_enddocs(void* a,void* b,void* c,void* d)
{
  SYSTEM_LOG(0,0,"on_xml_enddocs : %s, %s \r\n", (char*)b, (char*)c);
  //xmsgq_set(t, MAKELONG(COMPLETE, XML), (void*)info, 0);
  return 0;
}
void* on_xml_starttag(void* a,void* b,void* c,void* d)
{
  int e = 0;
  int s;
  //SYSTEM_LOG(0,0,"on_xml_starttag : %s, %s \r\n", (char*)b, (char*)c);

  //tagMTIFXML* p = (tagMTIFXML*)o;
  on_xml_parse(a,b,c,d);
  return 0;
}
void* on_xml_endtag(void* a,void* b,void* c,void* d)
{
  //SYSTEM_LOG(0,0,"on_xml_endtag : %s, %s \r\n", (char*)b, (char*)c);
  return 0;
}
void* on_xml_data(void* a,void* b,void* c,void* d)
{
  //SYSTEM_LOG(0,0,"on_xml_data : %s, %s \r\n", (char*)b, (char*)c);
  return 0;
}


int xml_read(void* h, void* msg, void* wparam, void* lparam)
{
  char path[256];
  int e = 0;
  mtifXML* p = (mtifXML*)h;
  info = (mtifInfo*)wparam;

  if ( lparam )
  {
    sprintf(path, "%s", (char*)lparam);
  }
  else
  {
    e = get_prefix(path);
    sprintf(&path[e], "/config.xml");
  }

  SYSTEM_LOG(0, 0, "path -> %s\r\n", path);

  p->m.pfxMTIF[ONSTARTDOCS] = on_xml_startdocs;
  p->m.pfxMTIF[ONENDDOCS]   = on_xml_enddocs;
  p->m.pfxMTIF[ONSTARTTAG]  = on_xml_starttag;
  p->m.pfxMTIF[ONENDTAG]    = on_xml_endtag;
  p->m.pfxMTIF[ONDATA]      = on_xml_data;


  memset(info, 0, sizeof(mtifInfo));

  mtifXMLOpen(&p->m, path, p);

  return 0;
}

int xml_status(void* h, void* msg, void* wparam, void* lparam)
{
  switch(LOWORD((unsigned int)msg))
  {
    case INIT:
    case READ:
      SYSTEM_LOG(0, 0, "XML READ\r\n");
      xml_read(h, msg, wparam, lparam);
      break;

    case COMPLETE:
      SYSTEM_LOG(0, 0, "XML Complete\r\n");
      //xmsgq_set(t, (void*)MAKELONG(INIT, XHTTP), wparam, lparam);

      //xmsgq_set(t, (void*)MAKELONG(INIT, SERIAL), wparam, lparam);
      //xmsgq_set(t, (void*)MAKELONG(INIT, XSOCKET), wparam, lparam);
      break;
  }

  return 0;
}
