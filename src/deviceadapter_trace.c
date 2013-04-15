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

DeviceAdapter *deviceadaptertrace_new(DeviceDriver *driver);

static int deviceadaptertrace_parse(DeviceAdapter *this, void *message);

void __attribute__ ((constructor)) anymote_plugin(void)
{
	fprintf(stderr, "%s\n", __FUNCTION__);
	DeviceAdapterFactory_loadadapter(DEVICEADAPTERTYPE_OTHER, NULL, deviceadaptertrace_new);
}

static DeviceAdapterOps g_ops =
{
	parse: deviceadaptertrace_parse,
};

DeviceAdapter *deviceadaptertrace_new(DeviceDriver *driver)
{
	void *privatedata = NULL;
	DeviceAdapter *this = NULL;

	this = deviceadapter_new(driver, DEVICEADAPTERTYPE_OTHER);
	deviceadapter_register(this, &g_ops, privatedata);
	return this;
}

int deviceadaptertrace_parse(DeviceAdapter *this, void *message)
{
	int ret = 0;

	anymotemessage_print(message);
	return ret;
}
