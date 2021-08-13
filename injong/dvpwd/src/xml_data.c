#include <mcommon.h>
#include <mxml.h>

static mtifInfo* info;

//int on_xml_data_parse(void* t,int sd,char* b,int sz,char* arg0,int arg1,void* o)
int on_xml_data_parse(void* a,void* b,void* c,void* d)
{
  int e = 0;
  char out[512];
  char enable[4];
  mtifXML* p = (mtifXML*)d;
  //SYSTEM_LOG(0, 0, "%s %s\r\n", b, arg0);

 
  if ( strncmp((char*)c, "data", 4) == 0 )
  {
    mtifXMLGetAttr(&p->m, 0, "name", out);
    mtifXMLGetAttr(&p->m, 0, "enable", enable);
    SYSTEM_LOG(0, 0, "%s enable=\"%s\"\r\n", out, enable);
    if ( *enable=='1' && strncmp(out, "SwitchInformation", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "dhcpmod",   info->arg[DATA][DATA_DHCPMOD]);
      mtifXMLGetAttr(&p->m, 0, "ipdata",    info->arg[DATA][DATA_IP]);
      mtifXMLGetAttr(&p->m, 0, "submask",   info->arg[DATA][DATAUB_MASK]);
      mtifXMLGetAttr(&p->m, 0, "gtwaddr",   info->arg[DATA][DATA_GTW_ADDR]);
    }
    else if ( *enable=='1' && strncmp(out, "FIRMWARE", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "ver",       info->arg[DATA][DATA_VER]);
    }
    else if ( *enable=='1' && strncmp(out, "PORT", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "port",      info->arg[DATA][DATA_PORT]);
      mtifXMLGetAttr(&p->m, 0, "status",    info->arg[DATA][DATATATUS]);
      mtifXMLGetAttr(&p->m, 0, "security",  info->arg[DATA][DATAECURITY]);
      mtifXMLGetAttr(&p->m, 0, "chntype",   info->arg[DATA][DATA_CHN_TYPE]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "AI", strlen(out))==0 )
    { 
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "port",      info->arg[DATA][DATA_PORT_AI]);
      mtifXMLGetAttr(&p->m, 0, "dttime",    info->arg[DATA][DATA_DT_TIME]);
      mtifXMLGetAttr(&p->m, 0, "databit",   info->arg[DATA][DATA_PACKET_TYPE]);
      mtifXMLGetAttr(&p->m, 0, "stopbit",   info->arg[DATA][DATA_ABNMSTS]);
    }
    else if ( *enable=='1' && strncmp(out, "SEED", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "mode",       info->arg[DATA][DATA_MODE_SEED]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "ARIA", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "mode",       info->arg[DATA][DATA_MODE_ARIA]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "LEA", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "mode",       info->arg[DATA][DATA_MODE_LEA]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
    }
     else if ( *enable=='1' && strncmp(out, "HIGHT", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "mode",       info->arg[DATA][DATA_MODE_HIGHT]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
    }
     else if ( *enable=='1' && strncmp(out, "HMAC", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "mode",       info->arg[DATA][DATA_MODE_HMAC]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
    }
     else if ( *enable=='1' && strncmp(out, "SHA256", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "mode",       info->arg[DATA][DATA_MODE_SHA256]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "LSH", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "mode",       info->arg[DATA][DATA_MODE_LSH]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "HASHDRBG", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "mode",       info->arg[DATA][DATA_MODE_HASHDRBG]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "OPENFLOW", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "opfsts",     info->arg[DATA][DATA_OPFSTS]);
      mtifXMLGetAttr(&p->m, 0, "ctrip",      info->arg[DATA][DATA_CTR_IP]);
      mtifXMLGetAttr(&p->m, 0, "ctrport",    info->arg[DATA][DATA_CTR_PORT]);
      mtifXMLGetAttr(&p->m, 0, "fallsts",    info->arg[DATA][DATA_FALLSTS]);
      mtifXMLGetAttr(&p->m, 0, "opfver",     info->arg[DATA][DATA_OPF_VER]);
      mtifXMLGetAttr(&p->m, 0, "status",     info->arg[DATA][DATA_OPF_STATUS]);
      mtifXMLGetAttr(&p->m, 0, "tbls",       info->arg[DATA][DATA_TBLS]);
      mtifXMLGetAttr(&p->m, 0, "flows",      info->arg[DATA][DATA_FLOWS]);
      mtifXMLGetAttr(&p->m, 0, "tblokp",     info->arg[DATA][DATA_TBLOKP]);
      mtifXMLGetAttr(&p->m, 0, "tbl_mch",    info->arg[DATA][DATA_TBL_MCH]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "FLOWS", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "flwmch",     info->arg[DATA][DATA_FLWMCH]);
      mtifXMLGetAttr(&p->m, 0, "inport",     info->arg[DATA][DATA_INPORT]);
      mtifXMLGetAttr(&p->m, 0, "attrtblid",  info->arg[DATA][DATA_ATTRTBLID]);
      mtifXMLGetAttr(&p->m, 0, "cookie",     info->arg[DATA][DATA_F_COOKIE]);
      mtifXMLGetAttr(&p->m, 0, "proty",      info->arg[DATA][DATA_F_PROTY]);
      mtifXMLGetAttr(&p->m, 0, "drt",        info->arg[DATA][DATA_F_DRT]);
      mtifXMLGetAttr(&p->m, 0, "hrdtime",    info->arg[DATA][DATA_F_HRDTIME]);
      mtifXMLGetAttr(&p->m, 0, "idletime",   info->arg[DATA][DATA_F_IDLETIME]);
      mtifXMLGetAttr(&p->m, 0, "bytecnt",    info->arg[DATA][DATA_F_BYTECNT]);
      mtifXMLGetAttr(&p->m, 0, "pkcnt",      info->arg[DATA][DATA_F_PKCNT]);
      mtifXMLGetAttr(&p->m, 0, "lstmch",     info->arg[DATA][DATA_F_LSTMCH]);
      mtifXMLGetAttr(&p->m, 0, "idsaplact",  info->arg[DATA][DATA_F_IDSAPLACT]);
      mtifXMLGetAttr(&p->m, 0, "optport",    info->arg[DATA][DATA_F_OPTPORT]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "METERS", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "tblid",      info->arg[DATA][DATA_M_TBLID]);
      mtifXMLGetAttr(&p->m, 0, "cookie",     info->arg[DATA][DATA_M_COOKIE]);
      mtifXMLGetAttr(&p->m, 0, "proty",      info->arg[DATA][DATA_M_PROTY]);
      mtifXMLGetAttr(&p->m, 0, "drt",        info->arg[DATA][DATA_M_DRT]);
      mtifXMLGetAttr(&p->m, 0, "hardtime",   info->arg[DATA][DATA_M_HARDTIME]);
      mtifXMLGetAttr(&p->m, 0, "idletime",   info->arg[DATA][DATA_M_IDLETIME]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "ACTIVEPORTLIST", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "activeport", info->arg[DATA][DATA_ACTIVEPORT]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
    }

    else if ( *enable=='1' && strncmp(out, "SECURITYMODE", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "secopt",     info->arg[DATA][DATAECOPT]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "ANOMALYPACKET", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "anomaly",     info->arg[DATA][DATA_ANOMALY]);
      mtifXMLGetAttr(&p->m, 0, "anomalycnt",  info->arg[DATA][DATA_ANOMALYCNT]);
      mtifXMLGetAttr(&p->m, 0, "wrom",        info->arg[DATA][DATA_WROM]);
      mtifXMLGetAttr(&p->m, 0, "wromcnt",     info->arg[DATA][DATA_WROMCNT]);
      mtifXMLGetAttr(&p->m, 0, "ddos",        info->arg[DATA][DATA_DDOS]);
      mtifXMLGetAttr(&p->m, 0, "ddoscnt",     info->arg[DATA][DATA_DDOSCNT]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
    }
    else if ( *enable=='1' && strncmp(out, "TODAYREVPACK", strlen(out))==0 )
    {
      info->arg[DATA][XM_ENABLE][0] = 'E';
      mtifXMLGetAttr(&p->m, 0, "hour",        info->arg[DATA][DATA_HOUR]);
      //xmsgq_set(p, (void*)MAKELONG(INIT, DATA), (void*)info, 0);
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
  on_xml_data_parse(a,b,c,d);
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
  
  if ( info->arg[TOP][XM_USR][0] )
  {
    sprintf(path, "%s", (char*)info->arg[TOP][XM_USR]);
  }
  else
  {
    e = get_prefix(path);
    sprintf(&path[e], "/devdata.xml");
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
      SYSTEM_LOG(0, 0, "XML_DATA READ\r\n");
      xml_read(h, msg, wparam, lparam);
      break;

    case COMPLETE:
      SYSTEM_LOG(0, 0, "XML_DATA Complete\r\n");
      //xmsgq_set(t, (void*)MAKELONG(INIT, XHTTP), wparam, lparam);

      //xmsgq_set(t, (void*)MAKELONG(INIT, SERIAL), wparam, lparam);
      //xmsgq_set(t, (void*)MAKELONG(INIT, DATA), wparam, lparam);
      break;
  }

  return 0;
}
