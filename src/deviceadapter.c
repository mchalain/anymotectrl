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
#include <anymote/linuxinput.h>
#include <anymote/devicedriver.h>

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

DeviceAdapter *deviceadapter_new(DeviceDriver *driver, DeviceAdapterType type)
{
	DeviceAdapter *this = malloc(sizeof(DeviceAdapter)); /* malloc check: free OK if deviceadapter_destroy called*/
	memset(this, 0, sizeof(DeviceAdapter));
	if (driver == NULL)
	{
		fprintf(stderr, "%s: error null driver specified\n", __FUNCTION__);
		return NULL;
	}
	this->m_driver = driver;
	this->m_type = type;
#ifdef DEVICEADAPTER_CREATE_ON_NEW
	devicedriver_create(this->m_driver, (char *) "Alien", this->m_type);
#endif
	return this;
}

void deviceadapter_register(DeviceAdapter *this, DeviceAdapterOps *ops, void *privatedata)
{
	memcpy(&(this->f_ops), ops, sizeof(DeviceAdapterOps));
	this->m_privatedata = privatedata;
}

void deviceadapter_destroy(DeviceAdapter *this)
{
	if (this->m_driver)
		devicedriver_destroy(this->m_driver);
	free(this);
}

int deviceadapter_getname(DeviceAdapter *this, char *buffer, int len)
{
	strncpy(buffer, "AnymoteDevice", len);
	return 0;
}
void *deviceadapter_privatedata(DeviceAdapter *this)
{
	return this->m_privatedata;
}

int deviceadapter_parse(DeviceAdapter *this, void *message)
{
	int ret = -1;
	void *datamsg = NULL;

	if ((datamsg = anymotemessage_getdevicename((AnymoteMessage *)message)) != NULL)
	{
		if (this->f_ops.check != NULL)
			ret = this->f_ops.check(this, datamsg);
		if (!this->m_connected)
		{
			log("connection from %s \n", (char *) datamsg);
#ifndef DEVICEADAPTER_CREATE_ON_NEW
			ret = devicedriver_create(this->m_driver, (char *) datamsg, this->m_type);
#else
			ret = 0;
#endif
			if ( ret >= 0)
			{
				this->m_connected |= 0x01;
				// in all case we want to continue to read this message by all deviceadpaters
				ret = 0;
			}
		}
		else
			ret = devicedriver_refresh(this->m_driver);
		free(datamsg);
	}
	else if (this->m_connected)
	{
		if (this->f_ops.parse != NULL)
			ret = this->f_ops.parse(this, message);
	}
	return ret;
}

int deviceadapter_sendevent(DeviceAdapter *this, DeviceAdapter_Event *event)
{
	int ret = -1;
	unsigned char *buffer;
	int len = EVENT_BUFFER_LEN;
	LinuxInputEvent *linuxevent = linuxinputevent_new(event);

	buffer = (unsigned char *)malloc(len + 1);/* malloc check: free OK*/
	memset(buffer, 0, len);
	do
	{
		do
		{
			ret = linuxinputevent_copy(linuxevent, buffer, len);
			if (ret <= 0)
			{
				linuxinputevent_destroy(linuxevent);
				free(buffer);
				return ret;
			}
			devicedriver_write(this->m_driver, buffer, ret);
		} while (ret != EVENT_BUFFER_LEN );
		ret = linuxinputevent_end(linuxevent);
	} while (ret > 0);
	linuxinputevent_destroy(linuxevent);
	free(buffer);

	return ret;
}
