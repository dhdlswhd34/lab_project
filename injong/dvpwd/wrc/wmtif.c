#if defined XWIN32
#include "wmtif.h"
#include "resource.h"

static wMTIF   wmtif;

void wmtif_command(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  char temp[32];

  switch(LOWORD(wparam))
  {
    case IDC_EDIT_PORT:

      break;

    case IDC_EDIT_BAUD:
      break;

    case IDC_BUTTON_NET_OPEN_CLOSE:
      break;


    case IDC_BUTTON_WS_OPEN_CLOSE:
      break;


    case IDC_BUTTON_OPEN_CLOSE:
      break;


    case IDC_BUTTON_OPEN_CLOSE2:
      break;

    case IDC_BUTTON_SEND:
      break;

    case IDC_BUTTON_WS_SEND:
      break;

    case IDC_BUTTON_WRITE:
      break;

    case IDC_BUTTON_WRITE2:
      break;


    case IDC_BUTTON_CLEAR:
      break;

    case IDC_CHECK_READ_YN:
      break;
  }    
}



void* wmtif_dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(msg)
  {
    case WM_COMMAND:
      wmtif_command(hwnd, msg, wparam, lparam);
      break;
    default:
      break;    
  }

  return 0;
}



void* wmtif_init(HWND hwnd)
{
  int e;
  void* hmod;

  wmtif.hitem[EDT_IP] = GetDlgItem(hwnd, IDC_EDIT_IP);
  wmtif.hitem[EDT_PORT] = GetDlgItem(hwnd, IDC_EDIT_PORT);
  wmtif.hitem[COMBO_PROTOCOL] = GetDlgItem(hwnd, IDC_COMBO_PROTOCOL);
  wmtif.hitem[COMBO_CS] = GetDlgItem(hwnd, IDC_COMBO_CS);
  wmtif.hitem[COMBO_CASTTYPE] = GetDlgItem(hwnd, IDC_COMBO_CASTTYPE);
  wmtif.hitem[BUTTON_NET_OPEN_CLOSE] = GetDlgItem(hwnd, IDC_BUTTON_NET_OPEN_CLOSE);
  wmtif.hitem[EDT_SEND] = GetDlgItem(hwnd, IDC_EDIT_SEND);
  wmtif.hitem[BUTTON_SEND] = GetDlgItem(hwnd, IDC_BUTTON_SEND);
  wmtif.hitem[CHECK_NET_CR] = GetDlgItem(hwnd, IDC_CHECK_NET_CR);
  wmtif.hitem[CHECK_NET_LF] = GetDlgItem(hwnd, IDC_CHECK_NET_LF);
  wmtif.hitem[COMBO_DISPLAY_TYPE_NET_W] = GetDlgItem(hwnd, IDC_COMBO_DISPLAY_TYPE_NET_W);
  wmtif.hitem[COMBO_DISPLAY_TYPE_NET_R] = GetDlgItem(hwnd, IDC_COMBO_DISPLAY_TYPE_NET_R);
  wmtif.hitem[EDT_SPORT] = GetDlgItem(hwnd, IDC_EDIT_SPORT);
  wmtif.hitem[EDT_BAUDRATE] = GetDlgItem(hwnd, IDC_EDIT_BAUD);
  wmtif.hitem[EDT_DBIT] = GetDlgItem(hwnd, IDC_EDIT_DBIT);
  wmtif.hitem[EDT_SBIT] = GetDlgItem(hwnd, IDC_EDIT_SBIT);
  wmtif.hitem[EDT_PBIT] = GetDlgItem(hwnd, IDC_EDIT_PBIT);
  wmtif.hitem[BTN_OPEN_CLOSE] = GetDlgItem(hwnd, IDC_BUTTON_OPEN_CLOSE);
  wmtif.hitem[COMBO_DISPLAY_TYPE_R] = GetDlgItem(hwnd, IDC_COMBO_DISPLAY_TYPE_R);
  wmtif.hitem[COMBO_DISPLAY_TYPE_W] = GetDlgItem(hwnd, IDC_COMBO_DISPLAY_TYPE_W);
  wmtif.hitem[EDT_WRITE] = GetDlgItem(hwnd, IDC_EDIT_WRITE);
  wmtif.hitem[BTN_WRITE] = GetDlgItem(hwnd, IDC_BUTTON_WRITE);
  wmtif.hitem[CHK_CR] = GetDlgItem(hwnd, IDC_CHECK_CR);
  wmtif.hitem[CHK_LF] = GetDlgItem(hwnd, IDC_CHECK_LF);
  wmtif.hitem[CHK_ROUTER] = GetDlgItem(hwnd, IDC_CHECK_ROUTER);
  wmtif.hitem[EDT_SPORT2] = GetDlgItem(hwnd, IDC_EDIT_SPORT2);
  wmtif.hitem[EDT_BAUDRATE2] = GetDlgItem(hwnd, IDC_EDIT_BAUD2);
  wmtif.hitem[EDT_DBIT2] = GetDlgItem(hwnd, IDC_EDIT_DBIT2);
  wmtif.hitem[EDT_SBIT2] = GetDlgItem(hwnd, IDC_EDIT_SBIT2);
  wmtif.hitem[EDT_PBIT2] = GetDlgItem(hwnd, IDC_EDIT_PBIT2);
  wmtif.hitem[BTN_OPEN_CLOSE2] = GetDlgItem(hwnd, IDC_BUTTON_OPEN_CLOSE2);
  wmtif.hitem[COMBO_DISPLAY_TYPE_R2] = GetDlgItem(hwnd, IDC_COMBO_DISPLAY_TYPE_R2);
  wmtif.hitem[COMBO_DISPLAY_TYPE_W2] = GetDlgItem(hwnd, IDC_COMBO_DISPLAY_TYPE_W2);
  wmtif.hitem[EDT_WRITE2] = GetDlgItem(hwnd, IDC_EDIT_WRITE2);
  wmtif.hitem[BTN_WRITE2] = GetDlgItem(hwnd, IDC_BUTTON_WRITE2);
  wmtif.hitem[CHK_CR2] = GetDlgItem(hwnd, IDC_CHECK_CR2);
  wmtif.hitem[CHK_LF2] = GetDlgItem(hwnd, IDC_CHECK_LF2);
  wmtif.hitem[LST_READ] = GetDlgItem(hwnd, IDC_LIST_READ);
  wmtif.hitem[CHK_READ_YN] = GetDlgItem(hwnd, IDC_CHECK_READ_YN);
  wmtif.hitem[BTN_CLEAR] = GetDlgItem(hwnd, IDC_BUTTON_CLEAR);
  wmtif.hitem[COMBO_WS_CS] = GetDlgItem(hwnd, IDC_COMBO_WS_CS);
  wmtif.hitem[EDIT_URL] = GetDlgItem(hwnd, IDC_EDIT_URL);
  wmtif.hitem[COMBO_DISPLAY_TYPE_WS_W] = GetDlgItem(hwnd, IDC_COMBO_DISPLAY_TYPE_WS_W);
  wmtif.hitem[COMBO_DISPLAY_TYPE_WS_R] = GetDlgItem(hwnd, IDC_COMBO_DISPLAY_TYPE_WS_R);
  wmtif.hitem[BUTTON_WS_OPEN_CLOSE] = GetDlgItem(hwnd, IDC_BUTTON_WS_OPEN_CLOSE);
	wmtif.hitem[EDIT_WS_SEND] = GetDlgItem(hwnd, IDC_EDIT_WS_SEND);
	wmtif.hitem[CHECK_WS_CR] = GetDlgItem(hwnd, IDC_CHECK_WS_CR);
	wmtif.hitem[CHECK_WS_LF] = GetDlgItem(hwnd, IDC_CHECK_WS_LF);
	wmtif.hitem[BUTTON_WS_SEND] = GetDlgItem(hwnd, IDC_BUTTON_WS_SEND);
  wmtif.hitem[CHECK_NET_LOG] = GetDlgItem(hwnd, IDC_CHECK_NET_LOG);
  wmtif.hitem[CHECK_WS_LOG] = GetDlgItem(hwnd, IDC_CHECK_WS_LOG);
  wmtif.hitem[CHECK_SERIAL_LOG] = GetDlgItem(hwnd, IDC_CHECK_SERIAL_LOG);
  wmtif.hitem[CHECK_SERIAL2_LOG] = GetDlgItem(hwnd, IDC_CHECK_SERIAL2_LOG);
  wmtif.hitem[CHECK_NET_ECHO] = GetDlgItem(hwnd, IDC_CHECK_NET_ECHO);
  wmtif.hitem[CHECK_WS_ECHO] = GetDlgItem(hwnd, IDC_CHECK_NET_ECHO);
  wmtif.hitem[CHECK_SERIAL_ECHO] = GetDlgItem(hwnd, IDC_CHECK_NET_ECHO);
  wmtif.hitem[CHECK_SERIAL2_ECHO] = GetDlgItem(hwnd, IDC_CHECK_NET_ECHO);

  SetText(wmtif.hitem[EDT_IP], "127.0.0.1", strlen("127.0.0.1"));
  SetText(wmtif.hitem[EDT_PORT], "7810", strlen("7810"));
  SetText(wmtif.hitem[BUTTON_SEND], "SEND", strlen("SEND"));
  SetText(wmtif.hitem[BUTTON_NET_OPEN_CLOSE], STR_OPEN, strlen(STR_OPEN));
  SetText(wmtif.hitem[BTN_WRITE], "WRITE", strlen("WRITE"));
  SetText(wmtif.hitem[BTN_OPEN_CLOSE], STR_OPEN, strlen(STR_OPEN));
  SetText(wmtif.hitem[BTN_CLEAR], "CLEAR", strlen("CLEAR"));
  SetText(wmtif.hitem[EDIT_URL], "http://127.0.0.1:7810/", strlen("http://127.0.0.1:7810/"));
  SetText(wmtif.hitem[BUTTON_WS_OPEN_CLOSE], STR_OPEN, strlen(STR_OPEN));
  SetText(wmtif.hitem[BUTTON_WS_SEND], "SEND", strlen("SEND"));

  ResetText(wmtif.hitem[EDT_SPORT], "COM1");
  ResetText(wmtif.hitem[EDT_BAUDRATE], "115200");
  ResetText(wmtif.hitem[EDT_DBIT], "8");
  ResetText(wmtif.hitem[EDT_SBIT], "1");
  ResetText(wmtif.hitem[EDT_PBIT], "0");

  ResetText(wmtif.hitem[EDT_SPORT2], "COM2");
  ResetText(wmtif.hitem[EDT_BAUDRATE2], "115200");
  ResetText(wmtif.hitem[EDT_DBIT2], "8");
  ResetText(wmtif.hitem[EDT_SBIT2], "1");
  ResetText(wmtif.hitem[EDT_PBIT2], "0");

  SendMessage(wmtif.hitem[COMBO_PROTOCOL], CB_ADDSTRING, 0, (LPARAM)"TCP");
  SendMessage(wmtif.hitem[COMBO_PROTOCOL], CB_ADDSTRING, 0, (LPARAM)"UDP");
  SendMessage(wmtif.hitem[COMBO_PROTOCOL], CB_SETCURSEL, 0, 0 );

  SendMessage(wmtif.hitem[COMBO_CS], CB_ADDSTRING, 0, (LPARAM)"SERVER");
  SendMessage(wmtif.hitem[COMBO_CS], CB_ADDSTRING, 0, (LPARAM)"CLIENT");
  SendMessage(wmtif.hitem[COMBO_CS], CB_SETCURSEL, 0, 0 );

  SendMessage(wmtif.hitem[COMBO_WS_CS], CB_ADDSTRING, 0, (LPARAM)"SERVER");
  SendMessage(wmtif.hitem[COMBO_WS_CS], CB_ADDSTRING, 0, (LPARAM)"CLIENT");
  SendMessage(wmtif.hitem[COMBO_WS_CS], CB_SETCURSEL, 0, 0 );

  SendMessage(wmtif.hitem[COMBO_CASTTYPE], CB_ADDSTRING, 0, (LPARAM)"UNICAST");
  SendMessage(wmtif.hitem[COMBO_CASTTYPE], CB_ADDSTRING, 0, (LPARAM)"BROADCAST");
  SendMessage(wmtif.hitem[COMBO_CASTTYPE], CB_ADDSTRING, 0, (LPARAM)"MULTICAST");
  SendMessage(wmtif.hitem[COMBO_CASTTYPE], CB_SETCURSEL, 0, 0 );

	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_NET_W], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_NET_W], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_NET_W], CB_SETCURSEL, 0, 0 );

	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_NET_R], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_NET_R], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_NET_R], CB_SETCURSEL, 0, 0 );

	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_WS_W], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_WS_W], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_WS_W], CB_SETCURSEL, 0, 0 );

	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_WS_R], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_WS_R], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_WS_R], CB_SETCURSEL, 0, 0 );

	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_W], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_W], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_W], CB_SETCURSEL, 0, 0 );

	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_R], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_R], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_R], CB_SETCURSEL, 0, 0 );

	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_W2], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_W2], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_W2], CB_SETCURSEL, 0, 0 );

	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_R2], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_R2], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(wmtif.hitem[COMBO_DISPLAY_TYPE_R2], CB_SETCURSEL, 0, 0 );


  InitListView(wmtif.hitem[LST_READ]);

  return 0;
}

#endif