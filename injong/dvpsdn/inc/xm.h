#ifndef __XM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __XM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#pragma comment(lib, "mtif.lib")
#pragma comment(lib, "libxcore.lib")


#if defined XWIN32
#include <wcommon.h>
//#include <wmtif.h>
#endif

#include <mcommon.h>
#include <mxml.h>
#include <mserial.h>
#include <msocket.h>
#include <mpacket.h>
#include <mwebsocket.h>
#include <mhttp.h>

#if defined LINUX


#elif defined XWIN32
#include "resource.h"
#define TAB_LEFT_MARGIN    12
#define TAB_TOP_MARGIN     8   
enum
{
  WMTIF,
  WDRAW,
  WPRIME,
  WBITMAP,
  WWSC,
  MAX_TAB
};

enum
{
  TAB_CONTROL,
  MAX_WND_ITEM
};
static int SHOW_MODE[MAX_TAB] = {SW_SHOW, SW_HIDE, SW_HIDE, SW_HIDE, SW_HIDE};
#endif


#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
#if defined PACKED
__attribute__((packed))
#endif
{
  mtifInfo             info;
  mtifXML              mxml;
  mtifSerial           msrl;
  mtifPacket           mpkt;
  mtifSocket           msck;
  mtifWebSocket        mws;
  mtifHttp             mhttp;
  //tagRAM               mram;
  //tagMTIFHTTP          mhttp;
  //tagMTIFSSL           mssl;
  //tagMTIFSocket        msck;
  //tagMTIFWebSocket     mws;
  //tagMTIFWebSocketS    mwsS;
  //tagMTIFSerial        msrl;
  //tagMTIFwfm           mwfm;
  //tagMTIFgpsm          mgpsm;
} MTIF;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif




#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
#if defined PACKED
__attribute__((packed))
#endif
{
  MTIF      mtif;
  #if defined LINUX
  #elif defined XWIN32
  HINSTANCE hinst[2];
  HWND      hdlg;
  HWND      htabwnd[MAX_TAB];
  HWND      hitem[MAX_WND_ITEM];
  RECT      rct;
  HMODULE   hmdl;
  #endif
}XWND;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif





#endif
