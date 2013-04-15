#ifndef __DEVICEDRIVER_H__
#define __DEVICEDRIVER_H__

struct _DeviceDriver;
typedef struct _DeviceDriver DeviceDriver;

typedef struct
{
	int (*write)(DeviceDriver *this, unsigned char *buffer, int len);
	int (*create)(DeviceDriver *this, char *devicename, DeviceAdapterType type);
	int (*refresh)(DeviceDriver *this);
	void (*destroy)(DeviceDriver *this);
} DeviceDriverOps;

DeviceDriver *devicedriver_new(char *devicepath);
void devicedriver_register(DeviceDriver *this, DeviceDriverOps *ops);
void devicedriver_destroy(DeviceDriver *this);
int devicedriver_create(DeviceDriver *this, char *devicename, DeviceAdapterType type);
int devicedriver_refresh(DeviceDriver *this);
int devicedriver_write(DeviceDriver *this, unsigned char *buffer, int len);

DeviceDriver *devicedriveruinput_new(char *devicepath);

#endif