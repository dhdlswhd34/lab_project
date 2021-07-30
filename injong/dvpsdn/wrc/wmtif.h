#ifndef __WMTIFWND_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __WMTIFWND_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#if defined XWIN32

#include <wcommon.h>

//#include <mhttp.h>
//#include <mserial.h>
//#include <msocket.h>




#define STR_OPEN      "OPEN"
#define STR_CLOSE     "CLOSE"



enum
{
  EDT_IP = 0,
  EDT_PORT,
  COMBO_PROTOCOL,
  COMBO_CS,
  COMBO_CASTTYPE,
  BUTTON_NET_OPEN_CLOSE,
  EDT_SEND,
  BUTTON_SEND,
  CHECK_NET_CR,
  CHECK_NET_LF,
  COMBO_DISPLAY_TYPE_NET_W,
  COMBO_DISPLAY_TYPE_NET_R,
  EDT_SPORT,
  EDT_BAUDRATE,
  EDT_DBIT,
  EDT_SBIT,
  EDT_PBIT,
  BTN_OPEN_CLOSE,
  COMBO_DISPLAY_TYPE_W,
  COMBO_DISPLAY_TYPE_R,
  EDT_WRITE,
  BTN_WRITE,
  CHK_CR,
  CHK_LF,
  CHK_ROUTER,
  EDT_SPORT2,
  EDT_BAUDRATE2,
  EDT_DBIT2,
  EDT_SBIT2,
  EDT_PBIT2,
  BTN_OPEN_CLOSE2,
  COMBO_DISPLAY_TYPE_W2,
  COMBO_DISPLAY_TYPE_R2,
  EDT_WRITE2,
  BTN_WRITE2,
  CHK_CR2,
  CHK_LF2,
  BTN_CLEAR,
  LST_READ,
  CHK_READ_YN,
	EDIT_URL,
  COMBO_WS_CS,
	COMBO_DISPLAY_TYPE_WS_W,
	COMBO_DISPLAY_TYPE_WS_R,
	BUTTON_WS_OPEN_CLOSE,
	EDIT_WS_SEND,
	CHECK_WS_CR,
	CHECK_WS_LF,
	BUTTON_WS_SEND,
  CHECK_NET_LOG,
  CHECK_WS_LOG,
  CHECK_SERIAL_LOG,
  CHECK_SERIAL2_LOG,
  CHECK_NET_ECHO,
  CHECK_WS_ECHO,
  CHECK_SERIAL_ECHO,
  CHECK_SERIAL2_ECHO,
  MAX_ITEM
};


#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  wLog               log;
  unsigned char      wshdr[1024];
  HWND               hitem[MAX_ITEM];
  unsigned char      read_lock;
}wMTIF;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif

void* wmtif_dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
void* wmtif_init(HWND hwnd);

#endif

#endif