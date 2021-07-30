#ifndef __WCOMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __WCOMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#if defined XWIN32
#include <xcommon.h>
#include <commctrl.h>

#pragma comment(lib, "comctl32.lib")


#define TOP_LOG_PATH             "log"
#define TOP_LOG_NAME             "dnap32"
#define LISTVIEW_MAX_LINE        0xFFFF


#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  FILE* fp;
  char pfname[80];
}wLog;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif

void SetFont(HWND hwnd, void* hdl);
void ResetText(HWND hwnd, char* msg);
int SetText(HWND hwnd, char* msg, int len);
int AppendText(HWND hwnd, char* msg, int len);
int GetText(HWND hwnd, char* msg, int len);
int GetComboText(HWND hwnd, char* txt);
void InitListView(HWND hwnd);
void ClearListView(HWND hwnd);
void InsertLVText(HWND hwnd,const char* fmt, ...);
void LogWrite(HWND hwnd, wLog* p, char* fname, char* pfx, const char* fmt, ...);
#endif

#endif
