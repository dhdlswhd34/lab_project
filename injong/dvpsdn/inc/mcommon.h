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
  XML,
  XWFM,
  GPSM,
  SERTEST,
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
  XM_TOTAL
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
}
mtifInfo;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif

#endif
