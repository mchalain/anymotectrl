#ifndef __DEVICEADAPTER_H__
#define __DEVICEADAPTER_H__

typedef enum
{
	DEVICEADAPTERTYPE_KBD,
	DEVICEADAPTERTYPE_MOUSE,
	DEVICEADAPTERTYPE_REMOTE,
	DEVICEADAPTERTYPE_OTHER,
	DEVICEADAPTERTYPE_MAX
} DeviceAdapterType;

struct _DeviceAdapter;
typedef struct _DeviceAdapter DeviceAdapter;

typedef struct
{
	int (*parse)(DeviceAdapter *this, void *message);
	int (*check)(DeviceAdapter *this, void *versionname);
} DeviceAdapterOps;

typedef enum
{
	KEYACTION_UP,
	KEYACTION_DOWN,
	KEYACTION_DOWNUP,
} DeviceAdapter_KeyAction;

typedef enum
{
	DATATYPE_STRING,
} DeviceAdapter_DataType;

typedef struct
{
	short m_keycode;
	long m_value;
	char m_action;
} DeviceAdapter_KeyEvent;

typedef struct
{
	long m_xdelta;
	long m_ydelta;
} DeviceAdapter_MouseEvent;

typedef struct
{
	long m_xscroll;
	long m_yscroll;
} DeviceAdapter_MouseWheel;

typedef enum
{
	EVENTTYPE_KEYEVENT  = 0,
	EVENTTYPE_MOUSEEVENT = 1,
	EVENTTYPE_MOUSEWHEEL = 2,
} EventType;

typedef struct
{
	EventType m_type;
	DeviceAdapter_KeyEvent m_keyevent;
	DeviceAdapter_MouseEvent m_mouseevent;
	DeviceAdapter_MouseWheel m_mousewheel;
} DeviceAdapter_Event;


#include "anymote.h"
#include "devicedriver.h"

DeviceAdapter *deviceadapter_new(DeviceDriver *driver, DeviceAdapterType type);
void deviceadapter_destroy(DeviceAdapter *this);
void deviceadapter_register(DeviceAdapter *this, DeviceAdapterOps *ops, void *privatedata);
int deviceadapter_getname(DeviceAdapter *this, char *buffer, int len);
void *deviceadapter_privatedata(DeviceAdapter *this);
int deviceadapter_parse(DeviceAdapter *this, void *message);
int deviceadapter_sendevent(DeviceAdapter *this, DeviceAdapter_Event *event);
#endif