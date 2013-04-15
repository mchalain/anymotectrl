#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef FUSD
#include <fusd.h>
#endif

#include <anymote/anymote.h>
#include <anymote/deviceadapter.h>
#include <anymote/linuxinput.h>
#include <anymote/deviceadapterfactory.h>
#include <anymote/kbdmapping.h>
#include <anymote/debug.h>

#define DEFAULTMAPFILENAME SHAREDIR"/defaultmap.bin"

DeviceAdapter *deviceadapterkbd_new(DeviceDriver *driver);

static int deviceadapterkbd_parse(DeviceAdapter *this, void *message);
static int deviceadapterkbd_sendstring(DeviceAdapter *this, char *string);
static unsigned char deviceadapterkbd_unmap(DeviceAdapter *this, char value, short *keycode);
static short deviceadapterkbd_convertkey(DeviceAdapter *this, short keycode);
static void *deviceadapterkbd_loadmap(DeviceAdapter *this, char *filename);

void __attribute__ ((constructor)) anymote_plugin(void)
{
	fprintf(stderr, "%s\n", __FUNCTION__);
	DeviceAdapterFactory_loadadapter(DEVICEADAPTERTYPE_KBD, NULL, deviceadapterkbd_new);
}

struct _DeviceAdapter
{
	unsigned char m_type:4;
	unsigned char m_connected:1;

	char *m_name;
	char *m_path;
	DeviceDriver *m_driver;
	DeviceAdapterOps f_ops;

	void *m_privatedata;
};

static DeviceAdapterOps g_ops =
{
	parse: deviceadapterkbd_parse,
};

DeviceAdapter *deviceadapterkbd_new(DeviceDriver *driver)
{
	void *privatedata = NULL;
	DeviceAdapter *this = NULL;

	this= deviceadapter_new(driver, DEVICEADAPTERTYPE_KBD);

	privatedata = deviceadapterkbd_loadmap(this, DEFAULTMAPFILENAME);
	deviceadapter_register(this, &g_ops, privatedata);
	return this;
}

static int deviceadapterkbd_parse(DeviceAdapter *this, void *message)
{
	int ret = -1;
	void *datamsg = NULL;
	DeviceAdapter_DataType type = 0;

	log("%s: message \n", __FUNCTION__);
	if ((datamsg = (char *)anymotemessage_getdata(message, &type)) != NULL)
	{
		switch(type)
		{
			case DATATYPE_STRING:
			{
				ret = deviceadapterkbd_sendstring(this, (char *) datamsg);
				free(datamsg);
			}
			break;
		}
	}
	else if ((datamsg = (char *)anymotemessage_getevent(message)) != NULL)
	{
		DeviceAdapter_Event *event = (DeviceAdapter_Event *) datamsg;
		if (event->m_type == EVENTTYPE_KEYEVENT && event->m_keyevent.m_keycode < 255)
		{
			event->m_keyevent.m_keycode = deviceadapterkbd_convertkey(this, event->m_keyevent.m_keycode);
			ret = deviceadapter_sendevent(this, event);
		}
		free(datamsg);
	}
	return ret;
}

static int deviceadapterkbd_sendstring(DeviceAdapter *this, char *string)
{
	DeviceAdapter_Event *event;
	int i;
	int len = strlen(string);

	for (i = 0; i < len; i++)
	{
		short keycode = 0;
		unsigned char modifier;

		event = malloc(sizeof(DeviceAdapter_Event));/* malloc check: free OK*/
		if ((modifier = deviceadapterkbd_unmap(this, string[i], &keycode)) != 0)
		{
			// modifier press
			memset(event, 0,sizeof(DeviceAdapter_Event));
			event->m_type = EVENTTYPE_KEYEVENT;
			event->m_keyevent.m_keycode = modifier;
			event->m_keyevent.m_action = KEYACTION_DOWN;
			deviceadapter_sendevent(this, event);
		}
		log("receive string %c, keycode %d\n", string[i], keycode);
		memset(event, 0,sizeof(DeviceAdapter_Event));
		event->m_type = EVENTTYPE_KEYEVENT;
		event->m_keyevent.m_keycode = keycode;
		event->m_keyevent.m_action = KEYACTION_DOWNUP;
		deviceadapter_sendevent(this, event);
		if (modifier != 0)
		{
			// modifier press
			memset(event, 0,sizeof(DeviceAdapter_Event));
			event->m_type = EVENTTYPE_KEYEVENT;
			event->m_keyevent.m_keycode = modifier;
			event->m_keyevent.m_action = KEYACTION_UP;
			deviceadapter_sendevent(this, event);
		}
		free(event);
	}
	return i;
}

static unsigned char deviceadapterkbd_unmap(DeviceAdapter *this, char value, short *keycode)
{
	unsigned short *ascii_keyboard = this->m_privatedata;//deviceadapter_privatedata(this);
	unsigned char modifier = 0;
	// fprintf(stderr, "value %X => %d\n", value, ascii_qwerty[value & 0x00FF]);
	log("value %X => %d\n", value, ascii_qwerty[value & 0x00FF]);
	*keycode = ascii_keyboard[value & 0x00FF];
	if (*keycode > 0x00FF)
	{
		modifier = ((*keycode) >> 8) & 0x00FF;
		*keycode &= 0x00FF;
	}
	return modifier;
}

static short deviceadapterkbd_convertkey(DeviceAdapter *this, short keycode)
{
	switch (keycode)
	{
		case 67:
			return KEY_BACKSPACE;
		break;
		case 66:
			return KEY_ENTER;
		default:
			//fprintf(stderr, "keycode %d 0x%X\n", keycode, keycode);
			return 0;
	}
	return 0;
}

static void *deviceadapterkbd_loadmap(DeviceAdapter *this, char *filename)
{
	int fd = 0;
	void *map = NULL;

	fd = open(filename, O_RDONLY);
	if (fd > 0)
	{
		int len = 0;
		int maplen = 0;

		maplen = lseek(fd, 0, SEEK_END);
		lseek(fd, 0, SEEK_SET);

		map = malloc(maplen);
		memset(map, 0, maplen);

		do
		{
			len = read(fd, map + len, maplen -len);
		} while (len > 0);
		close(fd);
	}
	return map;
}
