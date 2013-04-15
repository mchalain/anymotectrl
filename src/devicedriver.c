#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <anymote/anymote.h>
#include <anymote/devicedriver.h>
#include <anymote/linuxinput.h>

struct _DeviceDriver
{
	char *m_name;
	char *m_path;
	DeviceDriverOps f_ops;

	void *m_privatedata;
};

DeviceDriver *devicedriver_new(char *devicepath)
{
	DeviceDriver *this;
	this = malloc(sizeof(DeviceDriver));/* malloc check: free OK if devicedriver_destroy called */
	memset(this, 0, sizeof(DeviceDriver));
	if (devicepath)
	{
		this->m_path = malloc(strlen(devicepath) + 1);/* malloc check: free OK if devicedriver_destroy called */
		strcpy(this->m_path, devicepath);
	}
	return this;
}

void devicedriver_register(DeviceDriver *this, DeviceDriverOps *ops)
{
	memcpy(&(this->f_ops), ops, sizeof(DeviceDriverOps));
}

void devicedriver_destroy(DeviceDriver *this)
{
	if (this->f_ops.destroy)
		this->f_ops.destroy(this);

	if (this->m_path)
		free(this->m_path);
	if (this->m_name)
		free(this->m_name);
	free(this);
}

int devicedriver_create(DeviceDriver *this, char *devicename, DeviceAdapterType type)
{
	int len = strlen(devicename);

	this->m_name = malloc(len + 1);/* malloc check: free OK if devicedriver_destroy called */
	memset(this->m_name, 0, len + 1);
	strcpy(this->m_name, devicename);

	if ( this->f_ops.create)
		return this->f_ops.create(this, devicename, type);
	else
		return -1;
}

int devicedriver_refresh(DeviceDriver *this)
{
	if ( this->f_ops.refresh)
		return this->f_ops.refresh(this);
	else
		return 0;
}

int devicedriver_write(DeviceDriver *this, unsigned char *buffer, int len)
{
	if (this->f_ops.write)
		return this->f_ops.write(this, buffer, len);
	else
		return -1;
}

