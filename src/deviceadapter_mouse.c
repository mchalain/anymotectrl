#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <anymote/anymote.h>
#include <anymote/deviceadapter.h>
#include <anymote/deviceadapterfactory.h>
#include <anymote/linuxinput.h>
#include <anymote/debug.h>

#define FLINGVALUE 60

DeviceAdapter *deviceadaptermouse_new(DeviceDriver *driver);

static int deviceadaptermouse_parse(DeviceAdapter *this, void *message);

void __attribute__ ((constructor)) anymote_plugin(void)
{
	DeviceAdapterFactory_loadadapter(DEVICEADAPTERTYPE_MOUSE, NULL, deviceadaptermouse_new);
}

static DeviceAdapterOps g_ops =
{
	parse: deviceadaptermouse_parse,
};

DeviceAdapter *deviceadaptermouse_new(DeviceDriver *driver)
{
	void *privatedata = NULL;
	DeviceAdapter *this = NULL;

	this = deviceadapter_new(driver, DEVICEADAPTERTYPE_MOUSE);
	deviceadapter_register(this, &g_ops, privatedata);
	return this;
}

int deviceadaptermouse_parse(DeviceAdapter *this, void *message)
{
	int ret = 0;
	void *datamsg = NULL;

	if ((datamsg = (char *)anymotemessage_getevent(message)) != NULL)
	{
		DeviceAdapter_Event *event = (DeviceAdapter_Event *) datamsg;
		if (event->m_type == EVENTTYPE_KEYEVENT )
		{
			if ((event->m_keyevent.m_keycode >= BTN_MOUSE) &&  (event->m_keyevent.m_keycode < BTN_TASK))
				ret = deviceadapter_sendevent(this, event);
			else if (event->m_keyevent.m_keycode == 0x290)
			{
				event->m_keyevent.m_keycode = BTN_MOUSE;
				ret = deviceadapter_sendevent(this, event);
				event->m_keyevent.m_keycode = 0x290;
			}
			else if (event->m_keyevent.m_keycode == 0x73)
			{
				event->m_keyevent.m_keycode = BTN_MOUSE;
				ret = deviceadapter_sendevent(this, event);
				ret = deviceadapter_sendevent(this, event);
				event->m_keyevent.m_keycode = 0x73;
			}
			else if (event->m_keyevent.m_keycode == 0x74)
			{
				event->m_keyevent.m_keycode = BTN_MOUSE;
				ret = deviceadapter_sendevent(this, event);
				ret = deviceadapter_sendevent(this, event);
				event->m_keyevent.m_keycode = 0x74;
			}
		}
		else if (event->m_type == EVENTTYPE_MOUSEEVENT )
		{
#ifdef MOUSEWHEEL_ON_MOUSEEVENT
			if (event->m_mouseevent.m_xdelta > FLINGVALUE )
			{
				DeviceAdapter_Event *tevent = malloc(sizeof(DeviceAdapter_Event));
				memset(tevent, 0, sizeof(DeviceAdapter_Event));
				tevent->m_type = EVENTTYPE_MOUSEWHEEL;
				tevent->m_mousewheel.m_xscroll = event->m_mouseevent.m_xdelta;
				ret = deviceadapter_sendevent(this, tevent);
				free(tevent);
			}
			else if (event->m_mouseevent.m_xdelta < -FLINGVALUE )
			{
				DeviceAdapter_Event *tevent = malloc(sizeof(DeviceAdapter_Event));
				memset(tevent, 0, sizeof(DeviceAdapter_Event));
				tevent->m_type = EVENTTYPE_MOUSEWHEEL;
				tevent->m_mousewheel.m_xscroll = event->m_mouseevent.m_xdelta;
				ret = deviceadapter_sendevent(this, tevent);
				free(tevent);
			}
			else if (event->m_mouseevent.m_ydelta > FLINGVALUE )
			{
				DeviceAdapter_Event *tevent = malloc(sizeof(DeviceAdapter_Event));
				memset(tevent, 0, sizeof(DeviceAdapter_Event));
				tevent->m_type = EVENTTYPE_MOUSEWHEEL;
				tevent->m_mousewheel.m_yscroll = event->m_mouseevent.m_ydelta;
				ret = deviceadapter_sendevent(this, tevent);
				free(tevent);
			}
			else if (event->m_mouseevent.m_ydelta < -FLINGVALUE )
			{
				DeviceAdapter_Event *tevent = malloc(sizeof(DeviceAdapter_Event));
				memset(tevent, 0, sizeof(DeviceAdapter_Event));
				tevent->m_type = EVENTTYPE_MOUSEWHEEL;
				tevent->m_mousewheel.m_yscroll = event->m_mouseevent.m_ydelta;
				ret = deviceadapter_sendevent(this, tevent);
				free(tevent);
			}
			else
#endif
			if (event->m_mouseevent.m_xdelta != 0 || event->m_mouseevent.m_ydelta != 0)
				ret = deviceadapter_sendevent(this, event);
		}
		else if (event->m_type == EVENTTYPE_MOUSEWHEEL )
		{
			ret = deviceadapter_sendevent(this, event);
		}
		free(datamsg);
	}
	return ret;
}
