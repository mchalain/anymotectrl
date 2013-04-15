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
#include <anymote/debug.h>

DeviceAdapter *deviceadaptermaster_new(DeviceDriver *driver);

static int deviceadaptermaster_parse(DeviceAdapter *this, void *message);
static int deviceadaptermaster_sendstring(DeviceAdapter *this, char *string);
static unsigned char deviceadaptermaster_unmap(DeviceAdapter *this, char value, short *keycode);
static short deviceadaptermaster_convertkey(DeviceAdapter *this, short keycode);
static void *deviceadaptermaster_loadmap(DeviceAdapter *this, char *filename);

void __attribute__ ((constructor)) anymote_plugin(void)
{
	fprintf(stderr, "%s\n", __FUNCTION__);
	DeviceAdapterFactory_loadadapter(DEVICEADAPTERTYPE_KBD, NULL, deviceadaptermaster_new);
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
	parse: deviceadaptermaster_parse,
};

DeviceAdapter *deviceadaptermaster_new(DeviceDriver *driver)
{
	void *privatedata = NULL;
	DeviceAdapter *this = NULL;

	this= deviceadapter_new(driver, DEVICEADAPTERTYPE_OTHER);

	deviceadapter_register(this, &g_ops, privatedata);
	return this;
}

static int deviceadaptermaster_parse(DeviceAdapter *this, void *message)
{
	int ret = -1;

	log("%s: message \n", __FUNCTION__);
	if ((seqNum = anymotemessage_getsequence(message)) != 0)
	{
		//receive ping
		if (anymotemessage_isempty(message))
		{
			// send pong
			AnymoteMessage *rem =anymotemessage_new(REMOTEMESSAGE);
			anymotemessage_newbuilder(rem);
		}
	}
	return ret;
}
