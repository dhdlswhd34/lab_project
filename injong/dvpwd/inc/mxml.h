#ifndef __MXML_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MXML_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <cCommon.h>
#include <mtifXML.h>

typedef struct
{
  XMTIFXML   m;
}mtifXML;

void* on_xml_startdocs(void*,void*,void*,void*);
void* on_xml_enddocs(void*,void*,void*,void*);
void* on_xml_starttag(void*,void*,void*,void*);
void* on_xml_endtag(void*,void*,void*,void*);
void* on_xml_data(void*,void*,void*,void*);

int xml_read(void*,void*,void*,void*);
int xml_status(void*,void*,void*,void*);

#endif
