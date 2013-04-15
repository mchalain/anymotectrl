#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/uinput.h>

#include <anymote/anymote.h>
#include <anymote/devicedriver.h>
#include <anymote/linuxinput.h>
#include <anymote/deviceadapterfactory.h>
#include <anymote/debug.h>

#define DEVICEPATH "/dev/uinput"

char *typestring[]=
{
	"kbd",
	"mouse",
	"remote",
	"other",
};

struct _DeviceDriver
{
	char *m_name;
	char *m_path;
	DeviceDriverOps f_ops;

	void *m_privatedata;
};

DeviceDriver *devicedriveruinput_new(char *devicepath);
void devicedriveruinput_destroy(DeviceDriver *this);
static int devicedriveruinput_create(DeviceDriver *this, char *devicename, DeviceAdapterType type);
static int devicedriveruinput_refresh(DeviceDriver *this);
static int devicedriveruinput_write(DeviceDriver *this, unsigned char *buffer, int len);

static DeviceDriverOps g_ops =
{
	create : devicedriveruinput_create,
	refresh : devicedriveruinput_refresh,
	write : devicedriveruinput_write,
	destroy : devicedriveruinput_destroy,
};

void __attribute__ ((constructor)) anymote_plugin(void)
{
	DeviceAdapterFactory_loaddriver(NULL, devicedriveruinput_new);
}

typedef struct
{
	int m_devicefd;
	DeviceAdapterType m_type;
} DeviceDriverUinput;

DeviceDriver *devicedriveruinput_new(char *devicepath)
{
	DeviceDriverUinput *data;
	DeviceDriver *this = devicedriver_new(devicepath);
	devicedriver_register(this, &g_ops);

	if (!this->m_path)
	{
		this->m_path = malloc(strlen(DEVICEPATH) +1);/* malloc check: free OK if devicedriver_destroy called */
		strcpy(this->m_path, DEVICEPATH);
	}

	this->m_privatedata = malloc(sizeof(DeviceDriverUinput)); /* malloc check: free OK if devicedriveruinput_destroy called*/
	memset(this->m_privatedata, 0, sizeof(DeviceDriverUinput));
	data = (DeviceDriverUinput*)this->m_privatedata;
	data->m_devicefd = 0;
	return this;
}

void devicedriveruinput_destroy(DeviceDriver *this)
{
	DeviceDriverUinput *data = (DeviceDriverUinput*)this->m_privatedata;

	if (data->m_devicefd)
	{
		if(ioctl(data->m_devicefd, UI_DEV_DESTROY) < 0)
		{
			fprintf(stderr, "error to setup uinput: (%d) %s\n", errno, strerror(errno));
			return;
		}

		close(data->m_devicefd);
		data->m_devicefd = -1;
	}
	free(this->m_privatedata);
}

int devicedriveruinput_setupkbd(DeviceDriver *this)
{
	int i;
	DeviceDriverUinput *data = (DeviceDriverUinput*)this->m_privatedata;

	if(ioctl(data->m_devicefd, UI_SET_EVBIT, EV_KEY) < 0)
	{
		fprintf(stderr, "error to setup kbd(1) uinput: (%d) %s\n", errno, strerror(errno));
		return -1;
	}
	for (i = 0; i < KEY_MAX; i++)
	{
		if(ioctl(data->m_devicefd, UI_SET_KEYBIT, i) < 0)
		{
			fprintf(stderr, "error to setup kbd(2) uinput: (%d) %s\n", errno, strerror(errno));
			return -1;
		}
	}
	return 0;
}

int devicedriveruinput_setupremote(DeviceDriver *this)
{
	int i;
	DeviceDriverUinput *data = (DeviceDriverUinput*)this->m_privatedata;

	if(ioctl(data->m_devicefd, UI_SET_EVBIT, EV_MSC) < 0)
	{
		fprintf(stderr, "error to setup remote(1) uinput: (%d) %s\n", errno, strerror(errno));
		return -1;
	}
	if(ioctl(data->m_devicefd, UI_SET_EVBIT, EV_KEY) < 0)
	{
		fprintf(stderr, "error to setup remote(1) uinput: (%d) %s\n", errno, strerror(errno));
		return -1;
	}
	for (i = 0; i < KEY_MAX; i++)
	{
		if(ioctl(data->m_devicefd, UI_SET_KEYBIT, i) < 0)
		{
			fprintf(stderr, "error to setup remote(2) uinput: (%d) %s\n", errno, strerror(errno));
			return -1;
		}
	}
	return 0;
}

int devicedriveruinput_setupmouse(DeviceDriver *this)
{
	DeviceDriverUinput *data = (DeviceDriverUinput*)this->m_privatedata;
	int buttonid;

	if(ioctl(data->m_devicefd, UI_SET_EVBIT, EV_KEY) < 0)
	{
		fprintf(stderr, "error to setup mouse(1) uinput: (%d) %s\n", errno, strerror(errno));
		return -1;
	}
	for (buttonid = BTN_MOUSE; buttonid < BTN_TASK; buttonid++)
		if(ioctl(data->m_devicefd, UI_SET_KEYBIT, buttonid) < 0)
		{
			fprintf(stderr, "error to setup mouse(2) uinput: (%d) %s\n", errno, strerror(errno));
			return -1;
		}
	if(ioctl(data->m_devicefd, UI_SET_EVBIT, EV_REL) < 0)
	{
		fprintf(stderr, "error to setup mouse(3) uinput: (%d) %s\n", errno, strerror(errno));
		return -1;
	}
	if(ioctl(data->m_devicefd, UI_SET_RELBIT, REL_X) < 0)
	{
		fprintf(stderr, "error to setup mouse(4) uinput: (%d) %s\n", errno, strerror(errno));
		return -1;
	}
	if(ioctl(data->m_devicefd, UI_SET_RELBIT, REL_Y) < 0)
	{
		fprintf(stderr, "error to setup mouse(5) uinput: (%d) %s\n", errno, strerror(errno));
		return -1;
	}
	if(ioctl(data->m_devicefd, UI_SET_RELBIT, REL_WHEEL) < 0)
	{
		fprintf(stderr, "error to setup mouse(6) uinput: (%d) %s\n", errno, strerror(errno));
		return -1;
	}
	if(ioctl(data->m_devicefd, UI_SET_RELBIT, REL_HWHEEL) < 0)
	{
		fprintf(stderr, "error to setup mouse(7) uinput: (%d) %s\n", errno, strerror(errno));
		return -1;
	}
	return 0;
}

int devicedriveruinput_setup(DeviceDriver *this, DeviceAdapterType type)
{
	switch(type)
	{
		case DEVICEADAPTERTYPE_KBD:
			return devicedriveruinput_setupkbd(this);
		break;

		case DEVICEADAPTERTYPE_MOUSE:
			return devicedriveruinput_setupmouse(this);
		break;
		case DEVICEADAPTERTYPE_REMOTE:
			return devicedriveruinput_setupremote(this);
		break;
		default:
		break;
	}
	return 0;
}

static int devicedriveruinput_create(DeviceDriver *this, char *devicename, DeviceAdapterType type)
{
	DeviceDriverUinput *data = (DeviceDriverUinput*)this->m_privatedata;
	char *path;
	struct uinput_user_dev *uidev;

	path = this->m_path;
	data->m_devicefd  = open(path, O_WRONLY | O_NONBLOCK);
	if (data->m_devicefd == -1)
	{
		fprintf(stderr, "error to open %s: (%d) %s\n", path, errno, strerror(errno));
		return -1;
	}
	data->m_type = type;

	devicedriveruinput_setup(this, type);

	uidev = malloc(sizeof(struct uinput_user_dev));/* malloc check: free OK*/
	memset(uidev, 0, sizeof(struct uinput_user_dev));
	snprintf(uidev->name, 12, "%s_%s", typestring[type], devicename);
	uidev->id.bustype = BUS_USB;
	uidev->id.vendor  = 0x1;
	uidev->id.product = 0x1;
	uidev->id.version = 1;

	if(write(data->m_devicefd, uidev, sizeof(struct uinput_user_dev)) < 0)
	{
		fprintf(stderr, "error to setup device uinput: (%d) %s\n", errno, strerror(errno));
		free(uidev);
		return -1;
	}
	free(uidev);

	if(ioctl(data->m_devicefd, UI_DEV_CREATE) < 0)
	{
		fprintf(stderr, "error to create uinput entry: (%d) %s\n", errno, strerror(errno));
		return -1;
	}

	return data->m_devicefd;
}

static int devicedriveruinput_refresh(DeviceDriver *this)
{
	DeviceDriverUinput *data = (DeviceDriverUinput*)this->m_privatedata;
	int ret = devicedriveruinput_setup(this, data->m_type);
	if (ret < 0)
		ret = 0;
	return ret;
}

static int devicedriveruinput_write(DeviceDriver *this, unsigned char *buffer, int len)
{
	DeviceDriverUinput *data = (DeviceDriverUinput*)this->m_privatedata;
	int ret = -1;
	ret = write(data->m_devicefd , buffer, len);
	return ret;
}

