#ifndef __MCOMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MCOMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <cCommon.h>
#include <common.h>

#define RESET_COUNT         1000000  
#define MAX_SYS_QUE_COUNT   1024
#define STX                 0x02
#define ETX                 0x03
#define DLMT                0x5E   /// '^'
#define COUNT_CALI   10

#define HTTP_PROTOCOL_VER  "1.1"

//#define OPEN_API_URL "http://data.chungbuk.go.kr/openapi-data/service/noiseinfo/noiseinfo?numOfRows=1095&pageNo=1"
#define OPEN_API_URL "http://data.chungbuk.go.kr:2222/openapi-data/service/noiseinfo/noiseinfo"
//#define OPEN_API_URL "http://210.104.148.81/openapi-data/service/noiseinfo/noiseinfo"
//#define OPEN_API_URL "http://bulksms.net/API.svc/sms/json/sendmessage"
//#define OPEN_API_URL_KV "username=newuser&password=newpasswd&msg=test&msisdn=9999999999&tagname=Demo&shortcode=8888&telcoId=5&"
//#define OPEN_API_URL "http://192.168.0.2/index.html"


enum
{
  XSOCKET = 0,
  XWEBSOCKET,
  XWEBSOCKET_S,
  XSSL,
  XSERIAL,
  XPACKET,
  XHTTP,
  XHTTPD,
  XML,
  XWFM,
	XSHM,
  XSHM_S,
  GPSM,
  SERTEST,
  TOP,
  DATA,
  SYSTEM_MAX
};

enum
{
  INIT = 0,
  RELEASE,
  OPEN,
  CLOSE,
  BROADCAST,
  WRITE,
  READ,
  IDLE,
  READY,
  CONNECT,
  DISCONNECT,
  COMPLETE,
};


enum
{
  XM_ENABLE = 0,
  XM_DELAY_0,
  XM_DELAY_1,
  XM_DELAY_2,
  XM_IP,
  XM_IFNAME,
  XM_PORT,
  XM_PROTO,
  XM_CSTYPE,
  XM_CASTTYPE,
  XM_URI,
  XM_HOME,
  XM_INDEX,
  XM_DESC,
  XM_BAUDRATE,
  XM_DATABIT,
  XM_STOPBIT,
  XM_PARITYBIT,
  XM_BLOCKMODE,
  XM_ECHOMODE,
  XM_AP_SSID,
  XM_AP_PW,
  XM_EST,
  XM_ESTID,
  XM_EPT,
  XM_ESI,
  XM_ESP,
	XM_KEY,
	XM_SIZE,
  XM_COUNT,
  XM_USR,
  XM_TOTAL
};

enum
{ 
  XM_ENABLE = 0,
  DATA_DHCPMOD,
  DATA_IP,
  DATA_SUB_MASK,
  DATA_GTW_ADDR,  //sinfo
  DATA_VER,       //firm
  DATA_PORT,
  DATA_STATUS,
  DATA_SECURITY,
  DATA_CHN_TYPE,  //port
  DATA_PORT_AI,
  DATA_DT_TIME,
  DATA_PACKET_TYPE,
  DATA_ABNMSTS,   //ai
  DATA_MODE_SEED,
  DATA_MODE_ARIA,
  DATA_MODE_LEA,
  DATA_MODE_HIGHT,
  DATA_MODE_HMAC,
  DATA_MODE_SHA256,
  DATA_MODE_LSH,
  DATA_MODE_HASHDRBG,
  DATA_OPFSTS,
  DATA_CTR_IP,
  DATA_CTR_PORT,
  DATA_FALLSTS,
  DATA_OPF_VER,
  DATA_OPF_STATUS,
	DATA_TBLS,
	DATA_FLOWS,
  DATA_TBLOKP,
  DATA_TBL_MCH,      //opf
  DATA_FLWMCH,
  DATA_INPORT,
  DATA_ATTRTBLID,
  DATA_F_COOKIE,
  DATA_F_PROTY,
  DATA_F_DRT,
  DATA_F_HRDTIME,
  DATA_F_IDLETIME,
  DATA_F_BYTECNT,
  DATA_F_PKCNT,
  DATA_F_LSTMCH,
  DATA_F_IDSAPLACT,
  DATA_F_OPTPORT,    //flows
  DATA_M_TBLID,
  DATA_M_COOKIE,
  DATA_M_PROTY,
  DATA_M_DRT,
  DATA_M_HARDTIME,
  DATA_M_IDLETIME,   //meters
  DATA_ACTIVEPORT,   //active
  DATA_SECOPT,       //security
  DATA_ANOMALY,
  DATA_ANOMALYCNT,
  DATA_WROM,
  DATA_WROMCNT,
  DATA_DDOS,
  DATA_DDOSCNT,      //anomalypkt
  DATA_HOUR,
  DATA_TOTAL
};





/***
#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
#if defined PACKED
__attribute__((packed))
#endif
{
  unsigned int SR;
  unsigned int COUNTER[32];
  unsigned int INT;
}
mtifREG;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif
***/


#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
#if defined PACKED
__attribute__((packed))
#endif
{
  char arg[SYSTEM_MAX][XM_TOTAL][32];
  char arg_data[SYSTEM_MAX][DATA_TOTAL][32];
}
mtifInfo;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif

#endif
