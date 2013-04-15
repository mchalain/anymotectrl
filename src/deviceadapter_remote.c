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
#include <anymote/remotekey.h>

#define DEFAULTMAPFILENAME SHAREDIR"/defaultremote.bin"

DeviceAdapter *deviceadapterremote_new(DeviceDriver *driver);

static int deviceadapterremote_parse(DeviceAdapter *this, void *message);
static short deviceadapterremote_convertkey(DeviceAdapter *this, short keycode);
static void *deviceadapterremote_loadmap(DeviceAdapter *this, char *filename);

void __attribute__ ((constructor)) anymote_plugin(void)
{
	fprintf(stderr, "%s\n", __FUNCTION__);
	DeviceAdapterFactory_loadadapter(DEVICEADAPTERTYPE_REMOTE, NULL, deviceadapterremote_new);
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
	parse: deviceadapterremote_parse,
};

DeviceAdapter *deviceadapterremote_new(DeviceDriver *driver)
{
	void *privatedata = NULL;
	DeviceAdapter *this = NULL;

	this = deviceadapter_new(driver, DEVICEADAPTERTYPE_REMOTE);
	privatedata = deviceadapterremote_loadmap(this, DEFAULTMAPFILENAME);
	if (privatedata == NULL)
		privatedata = (void *)keyremote;
	deviceadapter_register(this, &g_ops, privatedata);
	return this;
}

int deviceadapterremote_parse(DeviceAdapter *this, void *message)
{
	int ret = 0;
	void *datamsg = NULL;

	if ((datamsg = (char *)anymotemessage_getevent(message)) != NULL)
	{
		DeviceAdapter_Event *event = (DeviceAdapter_Event *) datamsg;
		if (event->m_type == EVENTTYPE_KEYEVENT )
		{
			unsigned short old_keycode = event->m_keyevent.m_keycode;
			//fprintf(stderr, "Keycode before %ld\n", event->m_keyevent.m_keycode);
			event->m_keyevent.m_keycode = deviceadapterremote_convertkey(this, event->m_keyevent.m_keycode);
			if ( event->m_keyevent.m_keycode)
				ret = deviceadapter_sendevent(this, event);
			//fprintf(stderr, "Keycode %ld\n", event->m_keyevent.m_keycode);
			event->m_keyevent.m_keycode = old_keycode;
		}
		free(datamsg);
	}
	return ret;
}

static short deviceadapterremote_convertkey(DeviceAdapter *this, short keycode)
{
	int i = 0;
	short (*keyremote)[2] = this->m_privatedata;//deviceadapter_privatedata(this);

	while (keyremote[i][0] != keycode && keyremote[i][0] != 0) i++;
	fprintf(stderr, "key %d: %d %X\n", i, keyremote[i][1], keyremote[i][1]);
	return keyremote[i][1];
}

static void *deviceadapterremote_loadmap(DeviceAdapter *this, char *filename)
{
	int fd = 0;
	char *map = NULL;

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
