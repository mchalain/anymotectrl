#ifndef __DEVICEADAPTERFACTORY_H__
#define __DEVICEADAPTERFACTORY_H__

#include "deviceadapter.h"
#include "devicedriver.h"

typedef void (Anymote_Plugin)(void);

typedef DeviceAdapter *(DeviceAdapter_New)(DeviceDriver *driver);
typedef DeviceDriver *(DeviceDriver_New)(char *devicepath);

int DeviceAdapterFactory_loadlibrary(char *dirpath);
void DeviceAdapterFactory_loadadapter(DeviceAdapterType type, char *dynamiclibraryname, DeviceAdapter_New *function);
void DeviceAdapterFactory_loaddriver(char *dynamiclibraryname, DeviceDriver_New *function);
DeviceAdapter *DeviceAdapterFactory_create(DeviceAdapterType type, char *devicename);

#endif
