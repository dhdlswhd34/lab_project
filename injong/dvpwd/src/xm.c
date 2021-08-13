#include <xm.h>
#if defined XWIN32
#include <wmtif.h>
#endif
static XWND  top;

void* top_status(void* hwnd, void* msg, void* wparam, void* lparam)
{
  switch(HIWORD((unsigned int)msg))
  {
    case XSOCKET:
      socket_status(&top.mtif.msck, msg, wparam, lparam);
      break;

    case XSHM:
      mshm_status(&top.mtif.mshm, msg, wparam, lparam);
      break;
      
    case XSHM_S:
      cxshm_s_status(&top.mtif.mshm_s, msg, wparam, lparam);
      break;  

    case XPACKET:
      #if defined LINUX
      packet_status(&top.mtif.mpkt, msg, wparam, lparam);
      #endif
      break;

    case XSSL:
      //ssl_status(&mtif.mssl, msg, wparam, lparam);
      break;

    case XWEBSOCKET:
      websocket_status(&top.mtif.mws, msg, wparam, lparam);
      break;

    case XWEBSOCKET_S:
      //websocketS_status(&mtif.mwsS, msg, wparam, lparam);
      break;

    case XSERIAL:
      serial_status(&top.mtif.msrl, msg, wparam, lparam);
      break;

    case XHTTP:
      http_status(&top.mtif.mhttp, msg, wparam, lparam);
      break;

    case XHTTPD:
      httpd_status(&top.mtif.mhttpd, msg, wparam, lparam);
      break;

    case XWFM:
      //mwfm_status(&mtif.mwfm, msg, wparam, lparam);
      break;

    case GPSM:
      //mgpsm_status(&mtif.mgpsm, msg, wparam, lparam);
      break;

    case XML:
      xml_status(&top.mtif.mxml, msg, wparam, lparam);
      break;
  }
}


#if defined XWIN32
void fxWM_INIT_TABCONTROL(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  TCITEM tci = {0};
  top.hitem[TAB_CONTROL] = GetDlgItem(hwnd, IDC_TAB_CONTROL);

  tci.mask = TCIF_TEXT;

  tci.pszText = "mtif";
  SendMessage(top.hitem[TAB_CONTROL], TCM_INSERTITEM, (WPARAM)(int)WMTIF, (LPARAM)&tci);

  tci.pszText = "axis";
  SendMessage(top.hitem[TAB_CONTROL], TCM_INSERTITEM, (WPARAM)(int)WDRAW, (LPARAM)&tci);

  //tci.pszText = "prime";
  //SendMessage(top.hitem[TAB_CONTROL], TCM_INSERTITEM, (WPARAM)(int)XPRIME, (LPARAM)&tci);

  //tci.pszText = "bitmap";
  //SendMessage(top.hitem[TAB_CONTROL], TCM_INSERTITEM, (WPARAM)(int)XBITMAP, (LPARAM)&tci);

  //tci.pszText = "websocket client";
  //SendMessage(top.hitem[TAB_CONTROL], TCM_INSERTITEM, (WPARAM)(int)XWSC, (LPARAM)&tci);

  GetClientRect(top.hitem[TAB_CONTROL], &top.rct);
  SendMessage(top.hitem[TAB_CONTROL], TCM_ADJUSTRECT, FALSE, (LPARAM)&top.rct);
}

void fxWM_INITDIALOG(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int _index = 0;

  init_rand();


  top.hdlg = hwnd;
  fxWM_INIT_TABCONTROL(hwnd, msg, wparam, lparam);

  top.htabwnd[WMTIF] = CreateDialogParam(top.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_MTIF), top.hitem[TAB_CONTROL], (DLGPROC)wmtif_dlgproc, lparam);
  SetParent(top.htabwnd[WMTIF], hwnd);
  SetWindowPos(top.htabwnd[WMTIF], 0, top.rct.left+TAB_LEFT_MARGIN, top.rct.top+TAB_TOP_MARGIN, top.rct.right, top.rct.bottom, SWP_NOZORDER|SWP_SHOWWINDOW);
  ShowWindow(top.htabwnd[WMTIF], SHOW_MODE[WMTIF]);

  //top.htabwnd[XDRAWWND] = CreateDialogParam(top.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_DRAW), top.hitem[TAB_CONTROL], (DLGPROC)xdraw_dlgproc, lparam);
  //SetParent(top.htabwnd[XDRAWWND], hwnd);
  //SetWindowPos(top.htabwnd[XDRAWWND], 0, top.rct.left+TAB_LEFT_MARGIN, top.rct.top+TAB_TOP_MARGIN, top.rct.right, top.rct.bottom, SWP_NOZORDER|SWP_SHOWWINDOW);
  //ShowWindow(top.htabwnd[XDRAWWND], SHOW_MODE[XDRAWWND]);


  //top.htabwnd[XPRIME] = CreateDialogParam(top.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_PRIME), top.hitem[TAB_CONTROL], (DLGPROC)xprime_dlgproc, lparam);
  //SetParent(top.htabwnd[XPRIME], hwnd);
  //SetWindowPos(top.htabwnd[XPRIME], 0, top.rct.left+TAB_LEFT_MARGIN, top.rct.top+TAB_TOP_MARGIN, top.rct.right, top.rct.bottom, SWP_NOZORDER|SWP_SHOWWINDOW);
  //ShowWindow(top.htabwnd[XPRIME], SHOW_MODE[XPRIME]);

  //top.htabwnd[XBITMAP] = CreateDialogParam(top.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_BITMAP), top.hitem[TAB_CONTROL], (DLGPROC)xbitmap_dlgproc, lparam);
  //SetParent(top.htabwnd[XBITMAP], hwnd);
  //SetWindowPos(top.htabwnd[XBITMAP], 0, top.rct.left + TAB_LEFT_MARGIN, top.rct.top + TAB_TOP_MARGIN, top.rct.right, top.rct.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
  //ShowWindow(top.htabwnd[XBITMAP], SHOW_MODE[XBITMAP]);

  //top.htabwnd[XWSC] = CreateDialogParam(top.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_WSC), top.hitem[TAB_CONTROL], (DLGPROC)xwsc_dlgproc, lparam);
  //SetParent(top.htabwnd[XWSC], hwnd);
  //SetWindowPos(top.htabwnd[XWSC], 0, top.rct.left + TAB_LEFT_MARGIN, top.rct.top + TAB_TOP_MARGIN, top.rct.right, top.rct.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
  //ShowWindow(top.htabwnd[XWSC], SHOW_MODE[XWSC]);

  for ( _index=0; ; _index++)
  {
    if ( SHOW_MODE[_index] == SW_SHOW )
    {
      break;
    }
  }  
  SendMessage(top.hitem[TAB_CONTROL], TCM_SETCURSEL, (WPARAM)_index, 0);


  InvalidateRect(top.hitem[TAB_CONTROL], 0, TRUE);
  wmtif_init(top.htabwnd[WMTIF]);
  //xdrawwnd_init(top.htabwnd[XDRAWWND]);
  //xmainwnd_init(top.htabwnd[XMAINWND]);
  //xprime_init(top.htabwnd[XPRIME]);
  //xbitmap_init(top.htabwnd[XBITMAP]);
  //xwsc_init(top.htabwnd[XWSC]);
}

void fxWM_COMMAND(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{


}



void fxWM_NOTIFY(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int idx = SendMessage(top.hitem[TAB_CONTROL], TCM_GETCURSEL, 0, 0);
  int i=0;

  for ( i=0 ; i<MAX_TAB ; i++ )
  {
    ShowWindow(top.htabwnd[i], (idx==i)?SW_SHOW:SW_HIDE);
  }
}





BOOL CALLBACK dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(msg)
  {
    case WM_INITDIALOG:
      fxWM_INITDIALOG(hwnd, msg, wparam, lparam);
      return TRUE;

    case WM_CREATE:
      return TRUE;


    case WM_COMMAND:
      fxWM_COMMAND(hwnd, msg, wparam, lparam);
      return TRUE;

    case WM_NOTIFY:
      fxWM_NOTIFY(hwnd, msg, wparam, lparam);
      return TRUE;

    case WM_PAINT:
      InvalidateRect(hwnd, 0, TRUE);      
      break;


    case WM_CLOSE:
    case WM_DESTROY:
      PostQuitMessage(0);
      break;      


    default:
      break;    
  }

  return 0;
}
#endif



#if defined LINUX
void setup(int argc, char** argv)
{
  sprintf(top.mtif.info.arg[TOP][XM_USR], argv[1]);
  xmsgq_set(&top.mtif.mxml, MAKELONG(INIT, XML), &top.mtif.info, argv[1]);

  top.mtif.mshm.pif = 
  top.mtif.msrl.pif =
  top.mtif.msck.pif =
  top.mtif.mws.pif = 
  top.mtif.mhttp.pif = 
  top.mtif.mhttpd.pif = 
  top.mtif.mpkt.pif = &top.mtif;
}
#elif defined XWIN32
void setup(HINSTANCE hinst, HINSTANCE hpinst, LPSTR cmd, int nshow)
{
  top.mtif.mhttp.m.h = 
  top.mtif.mhttpd.m.h = 
  top.mtif.msrl.m.h =
  top.mtif.mpkt.m.h =
  top.mtif.msck.m.h = 
  top.mtif.mws.m.h  = 
  top.mtif.mxml.m.h =
    LoadLibrary("xmtif.dll");

  top.hinst[0] = hinst;
  top.hinst[1] = hpinst;
  DialogBox(hinst, (LPCSTR)IDD_DIALOG, HWND_DESKTOP, (DLGPROC)dlgproc);
}
#endif


#if defined LINUX
int main(int argc, char** argv)
{
  setup(argc, argv);

  for( ; ; )
  {
    xmsgq_check(top_status);
    mcsleep(1);
  }

  return 0;
}
#elif defined XWIN32
int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hpinst, LPSTR cmd, int nshow)
{
  setup(hinst, hpinst, cmd, nshow);
  return TRUE;
}
#endif

