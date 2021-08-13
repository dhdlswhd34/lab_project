#include "wcommon.h"

#if defined XWIN32

void SetFont(HWND hwnd, void* hdl)
{
  SendMessage(hwnd, WM_SETFONT, (WPARAM)hdl, (LPARAM)FALSE);
}

void ResetText(HWND hwnd, char* msg)
{
  SendMessage(hwnd, EM_LIMITTEXT, (WPARAM)0xFFFFFFFF, 0);
  SendMessage(hwnd,  EM_SETSEL, 0, -1);
  if ( msg )
  {
    SendMessage(hwnd, EM_REPLACESEL, 1, (LPARAM)msg);
  }
  else
  {
    SendMessage(hwnd, WM_CLEAR, 0, 0);
  }
}

int SetText(HWND hwnd, char* msg, int len)
{
  SendMessage(hwnd, EM_LIMITTEXT, (WPARAM)0xFFFFFFFF, 0);
  return SendMessage(hwnd,  WM_SETTEXT, len, (LPARAM)msg);
}

int AppendText(HWND hwnd, char* msg, int len)
{
  int s,e,sz;
  SendMessage(hwnd, EM_LIMITTEXT, (WPARAM)0xFFFFFFFF, 0);
  SendMessage(hwnd, EM_GETSEL, (WPARAM)&s, (LPARAM)&e);
  sz = GetWindowTextLength(hwnd);
  SendMessage(hwnd, EM_SETSEL, sz, sz);
  SendMessage(hwnd, EM_REPLACESEL, 1, (LPARAM)msg);
  return SendMessage(hwnd,  EM_SETSEL, s, e);
}

int GetText(HWND hwnd, char* msg, int len)
{
  int e = SendMessage(hwnd, WM_GETTEXT, len, (LPARAM)msg);
  msg[e] = 0;
  return e;
}

int GetComboText(HWND hwnd, char* txt)
{
  int i=0;
  int e=0;
  i=SendMessage(hwnd, CB_GETCURSEL, 0, 0);
  e = SendMessage(hwnd, CB_GETLBTEXT, i, (LPARAM)txt);
  *(txt+e) = 0;
  return e;
}


void InitListView(HWND hwnd)
{
  LVCOLUMN lc;
  memset(&lc, 0, sizeof(LVCOLUMN));

  SendMessage(hwnd, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

  lc.mask = LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
  lc.cx = 30;
  lc.pszText = "no";
  SendMessage(hwnd, LVM_INSERTCOLUMN,0,(LPARAM)&lc);

  lc.cx = 900;
  lc.pszText = "Log";
  SendMessage(hwnd, LVM_INSERTCOLUMN,1,(LPARAM)&lc);
}

void ClearListView(HWND hwnd)
{
  SendMessage(hwnd, LVM_DELETEALLITEMS, 0, 0);
}

void InsertLVText(HWND hwnd,const char* fmt, ...)
{
  int no;
  char _no[32];
  char _msg[8192];
  va_list args;
  LVITEM li;

  memset(&li, 0, sizeof(LVITEM));

  no = (int)SendMessage(hwnd, LVM_GETITEMCOUNT, 0, 0);

  if ( no>LISTVIEW_MAX_LINE )
  {
    SendMessage(hwnd, LVM_DELETEALLITEMS, 0, 0);
    no = 0;
  }
  sprintf(_no, "%d", no);

  li.mask = LVIF_TEXT;
  li.iItem = no;
  li.iSubItem = 0;
  li.pszText = _no;
  SendMessage(hwnd, LVM_INSERTITEM, 0, (LPARAM)&li);

	va_start(args, fmt);
	vsprintf(_msg, fmt, args);
  li.iSubItem = 1;
  li.pszText = _msg;
  SendMessage(hwnd, LVM_SETITEM, 0, (LPARAM)&li);
  va_end(args);

  memset(&li, 0, sizeof(LVITEM));
  li.stateMask = LVIS_FOCUSED|LVIS_SELECTED;
  li.state = LVIS_FOCUSED|LVIS_SELECTED;

  SendMessage(hwnd, LVM_SETITEMSTATE, -1, (LPARAM)(LVITEM*)&li);

  li.state = LVIS_FOCUSED|LVIS_SELECTED;
  SendMessage(hwnd, LVM_SETITEMSTATE, no, (LPARAM)(LVITEM*)&li);
  SendMessage(hwnd, LVM_ENSUREVISIBLE, no, MAKELPARAM(0,0));
}

//
//FILE* Log(tagMTIFLog* l, char* fname, char* pfx, const char* fmt, ...)
//{
//  int e = 0;
//  char logf[128] = {0, };
//  char _msg[8192];
//  char path[32];
//  char tmp[32];
//  char tm[80];
//  int YY,MM,DD,hh,mm,ss;
//  va_list args;
//
//  get_curr_time(tm, ".", ".", ".", ".", &YY,&MM,&DD,&hh,&mm,&ss);
//
//  create_dir(TOP_LOG_PATH);
//  sprintf(path, "%s\\%04d.%02d",TOP_LOG_PATH,YY,MM);
//  create_dir(path);
//  
//  if ( l->fname[0] ) memcpy(logf, l->fname, strlen(l->fname));
//
//  sprintf(l->fname, "%s\\%s.%02d.%02d.log", path, fname, DD, hh);
//
//  if ( strncmp(l->fname, logf, strlen(l->fname)) != 0 )
//  {
//    if ( l->fp ) fclose(l->fp);
//    l->fp = fopen(l->fname, "a+");
//  }
//
//	va_start(args, fmt);
//	vsprintf(_msg, fmt, args);
//  va_end(args);
//
//  log_write(0x1C000000, l->fp, "%12s | %s\r\n", pfx, _msg);
//  fflush(l->fp);
//
//  return l->fp;
//}


void LogWrite(HWND hwnd, wLog* p, char* fname, char* pfx, const char* fmt, ...)
{
  va_list args;
  char _arg[8192];

  if ( SendMessage(hwnd, BM_GETCHECK, 0, 0) != BST_CHECKED )
  {
    return;
  }
	va_start(args, fmt);
	vsprintf(_arg, fmt, args);
  va_end(args);

  log_write_ex("log", fname, p->pfname, (void**)&p->fp, pfx, 0, _arg);
  //Log(l, TOP_LOG_NAME, pfx, _arg);
}

//
//FILE* LogWriteEx(int id, char* fname, char* pfname, char* pfx, const char* fmt, ...)
//{
//  va_list args;
//  char _arg[8192];
//
//  if ( SendMessage(mtif.hitem[id], BM_GETCHECK, 0, 0) != BST_CHECKED )
//  {
//    return;
//  }
//	va_start(args, fmt);
//	vsprintf(_arg, fmt, args);
//  va_end(args);
//
//  //Log(l, TOP_LOG_NAME, pfx, _arg);
//
//  return 0;
//
//}
//

#endif