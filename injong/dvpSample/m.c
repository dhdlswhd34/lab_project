#include <mtifSerial.h>
#include <stdio.h>
#include <cCommon.h>
#include <mtifSocket.h>
#include <mtifWebSocket.h>


void main()
{
  int  e =1;
  int p = 1;

  XMTIFSerial m;  
  //XMTIFSocket k;
  XMTIFWebSocket k;
  

  m.h = LoadLibrary("xmtif.dll");
  k.h = LoadLibrary("xmtif.dll");

  p = mtifSerialCreate(&m);
  printf(" e -> %d \r\n", e);
  printf(" p -> %d \r\n", p);
  e = mtifWebSocketCreate(&k);
  //e  = mtifSocketCreate(&k);
  printf("----------  \r\n");
  printf(" e -> %d \r\n", e);



  mtifSerialDestroy(&m);
  //mtifSocketDestroy(&k);
  mtifWebSocketDestroy(&k);
  printf(" End of Programs \r\n");



}