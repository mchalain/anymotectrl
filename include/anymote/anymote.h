#ifndef __ANYMOTE_H__
#define __ANYMOTE_H__

#ifndef log
#ifdef DEBUG
#define log printf
#else
#define log(...)
#endif
#endif

#define NEWLEVEL(x, y) (((x) << 3) | (y))
#define REMOTEMESSAGE		0
#define SEQNUM			NEWLEVEL(REMOTEMESSAGE , 1)
#define REQUESTMESSAGE		NEWLEVEL(REMOTEMESSAGE , 2)
#define RESPONSEMESSAGE		NEWLEVEL(REMOTEMESSAGE , 3)
// REQUESTMESSAGE
#define KEYEVENT		NEWLEVEL(REQUESTMESSAGE , 1)
#define MOUSEEVENT		NEWLEVEL(REQUESTMESSAGE , 2)
#define MOUSEWHEEL		NEWLEVEL(REQUESTMESSAGE , 3)
#define REQDATA			NEWLEVEL(REQUESTMESSAGE , 4)
#define CONNECT			NEWLEVEL(REQUESTMESSAGE , 5)
#define FLING			NEWLEVEL(REQUESTMESSAGE , 6)
// KEYEVENT
#define KEYCODE			NEWLEVEL(KEYEVENT , 1)
#define ACTION			NEWLEVEL(KEYEVENT , 2)
// MOUSEEVENT
#define XDELTA			NEWLEVEL(MOUSEEVENT , 1)
#define YDELTA			NEWLEVEL(MOUSEEVENT , 2)
// MOUSEEVENT
#define XSCROLL			NEWLEVEL(MOUSEWHEEL , 1)
#define YSCROLL			NEWLEVEL(MOUSEWHEEL , 2)
// CONNECT
#define DEVICENAME		NEWLEVEL(CONNECT , 1)
#define VERSION			NEWLEVEL(CONNECT , 2)
// DATA
#define DATATYPE		NEWLEVEL(REQDATA , 1)
#define DATADATA		NEWLEVEL(REQDATA , 2)
// FLING
#define URI			NEWLEVEL(FLING , 1)
typedef enum
{
	TagRemoteMessage = REMOTEMESSAGE,
	TagSeqNum = SEQNUM,
	TagRequestMessage = REQUESTMESSAGE,
	TagResponseMessage = RESPONSEMESSAGE,
	TagKeyEvent = KEYEVENT,
	TagMouseEvent = MOUSEEVENT,
	TagMouseWheel = MOUSEWHEEL,
	TagReqData = REQDATA,
	TagConnect = CONNECT,
	TagFling = FLING,
	TagKeyCode = KEYCODE,
	TagAction = ACTION,
	TagDeviceName = DEVICENAME,
	TagVersion = VERSION,
	TagXDelta = XDELTA,
	TagYDelta = YDELTA,
	TagXScroll = XSCROLL,
	TagYScroll = YSCROLL,
	TagDataType = DATATYPE,
	TagDataData = DATADATA,
	TagUri = URI
} AnymoteTag;
struct  _AnymoteMessage;
typedef struct  _AnymoteMessage  AnymoteMessage;

#include "deviceadapter.h"

AnymoteMessage *anymotemessage_new(int type);
void anymotemessage_destroy(AnymoteMessage *this);

unsigned char *anymotemessage_read(AnymoteMessage *this, unsigned char *buffer, unsigned long bufferlen);
void anymotemessage_print(AnymoteMessage *this);

char *anymotemessage_getdevicename(AnymoteMessage *this);
int anymotemessage_getsequence(AnymoteMessage *this);
DeviceAdapter_Event *anymotemessage_getevent(AnymoteMessage *this);
char *anymotemessage_getdata(AnymoteMessage *this, DeviceAdapter_DataType *type);

#endif