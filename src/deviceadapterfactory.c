#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dlfcn.h>
#include <dirent.h>

#include <anymote/deviceadapterfactory.h>

#define DEVICEADAPTERFACTORY_MAXENTRIES 1

struct _DeviceAdapterFactory
{
	struct
	{
		int m_nbentries;
		DeviceAdapter_New *m_newfunction[DEVICEADAPTERFACTORY_MAXENTRIES];
	} m_deviceadapter[DEVICEADAPTERTYPE_MAX + 1];
	struct
	{
		int m_nbentries;
		DeviceDriver_New *m_newfunction[DEVICEADAPTERFACTORY_MAXENTRIES];
	} m_devicedriver;
};

struct _DeviceAdapterFactory g_instancefactory = {0};
struct _DeviceAdapterFactory *g_factory = &g_instancefactory;

int DeviceAdapterFactory_loadlibrary(char *dirpath)
{
	DIR *dir = opendir(dirpath);
	struct dirent *entry = NULL;
	do
	{
		entry = readdir(dir);
		if (entry && strstr(entry->d_name, ".so") != NULL)
		{
			void *handle;
			char *path = NULL;
			Anymote_Plugin *anymote_plugin;

			path = malloc(strlen(dirpath)+strlen(entry->d_name) + 2); /* malloc check: free OK*/
			sprintf(path,"%s/%s", dirpath, entry->d_name);
			fprintf(stderr, "found library %s\n", entry->d_name);
			handle = dlopen(path, RTLD_LAZY);
			free(path);
			if (!handle)
			{
				fprintf(stderr, "error on plugin loading err : %s\n",dlerror());
				return -1;
			}
			anymote_plugin = dlsym(handle, "anymote_plugin");
			(*anymote_plugin)();
		}
	} while(entry != NULL);

	return 0;
}

void DeviceAdapterFactory_loadadapter(DeviceAdapterType type, char *dynamiclibraryname, DeviceAdapter_New *function)
{
	if (g_factory->m_deviceadapter[type].m_nbentries >= DEVICEADAPTERFACTORY_MAXENTRIES)
		return;
	if (function)
		g_factory->m_deviceadapter[type].m_newfunction[g_factory->m_deviceadapter[type].m_nbentries] = function;
	else if (dynamiclibraryname && strstr(dynamiclibraryname, "deviceadapter"))
	{
		Anymote_Plugin *anymote_plugin;
		void *handle = dlopen(dynamiclibraryname, RTLD_LAZY);
		if (!handle)
			return;
		anymote_plugin = dlsym(handle, "anymote_plugin");
		(*anymote_plugin)();
	}
	g_factory->m_deviceadapter[type].m_nbentries++;
}

void DeviceAdapterFactory_loaddriver(char *dynamiclibraryname, DeviceDriver_New *function)
{
	if (g_factory->m_devicedriver.m_nbentries >= DEVICEADAPTERFACTORY_MAXENTRIES)
		return;
	if (function)
		g_factory->m_devicedriver.m_newfunction[g_factory->m_devicedriver.m_nbentries] = function;
	else if (dynamiclibraryname && strstr(dynamiclibraryname, "devicedriver"))
	{
		Anymote_Plugin *anymote_plugin;
		void *handle = dlopen(dynamiclibraryname, RTLD_LAZY);
		if (!handle)
			return;
		anymote_plugin = dlsym(handle, "anymote_plugin");
		(*anymote_plugin)();
	}
	g_factory->m_devicedriver.m_nbentries++;
}

DeviceAdapter *DeviceAdapterFactory_create(DeviceAdapterType type, char *devicename)
{
	DeviceDriver *driver = NULL;
	DeviceAdapter *adapter = NULL;
	int i = 0;

	if (i < g_factory->m_devicedriver.m_nbentries && g_factory->m_devicedriver.m_newfunction[i] != NULL)
	{
		driver = (g_factory->m_devicedriver.m_newfunction[i])(devicename);
	}
	if (driver == NULL)
		fprintf(stderr, "No driver available!!!\n");

	i = 0;
	if (i < g_factory->m_deviceadapter[type].m_nbentries && g_factory->m_deviceadapter[type].m_newfunction[i] != NULL)
		adapter = (g_factory->m_deviceadapter[type].m_newfunction[i])(driver);
	return adapter;
}

