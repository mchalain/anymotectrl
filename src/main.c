#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>

#include <anymote/anymote.h>
#include <anymote/deviceadapter.h>
#include <anymote/deviceadapterfactory.h>
#include <anymote/debug.h>

#define BUFFER_LEN    256
#define DEVICEFILE "/tmp/anymote"

int main_loadlibrary(char *path);

int main(int argc, char **argv)
{
	int ret = 0;
	DeviceAdapter *deviceadapter[DEVICEADAPTERTYPE_MAX];
	int maxfd, serverfd;
	char *input = NULL;
	char *devicedir = NULL;
	char default_devicedir[] = ".";
	char *devicename[DEVICEADAPTERTYPE_MAX] = {0};
#ifdef GDB
	int largc = 4;
	char *largv[] = {"anymoteparser", "-i", DEVICEFILE, "/dev/uinput"};
	#warning default arguments use
#else
	int largc = argc;
	char **largv = argv;
#endif
	int i, j = 0;

	for (i = 1; i < largc; i++)
	{
		if (strncmp(largv[i], "-i", 2) == 0)
			input = largv[++i];
		else if (strncmp(largv[i], "-d", 2) == 0)
			devicedir = largv[++i];
		else
			devicename[j++] = largv[i];
	}

	if (input == NULL)
		return -1;

	if (devicedir == NULL && ((devicedir = getenv("ANYMOTEDIR")) == NULL))
		devicedir = default_devicedir;

	if (strncmp(input, "-", 1) == 0)
		serverfd = 0;
	else
		serverfd = open(input, O_RDWR);
	if (serverfd < 0)
		return -1;
	maxfd = serverfd;
#ifdef STATIC
	DeviceAdapterFactory_loadadapter(NULL, deviceadapterkbd_new);
	DeviceAdapterFactory_loadadapter(NULL, deviceadaptermouse_new);
#else
	DeviceAdapterFactory_loadlibrary(devicedir);
#endif
//	DeviceAdapterFactory_loaddriver(NULL, devicedriveruinput_new);

	for (i = 0; i < DEVICEADAPTERTYPE_MAX; i++)
		deviceadapter[i] = DeviceAdapterFactory_create(i, "/dev/uinput");

	do
	{
		fd_set rfds;

		FD_ZERO(&rfds);
		FD_SET(serverfd, &rfds);
		ret = select(maxfd + 1, &rfds, NULL, NULL, NULL);
		if (ret > 0 )
		{
			if (FD_ISSET(serverfd, &rfds) > 0)
			{
				unsigned char buffer[BUFFER_LEN];

				ret = read(serverfd, buffer, sizeof(buffer));
				AnymoteMessage *message = anymotemessage_new(REMOTEMESSAGE);
				anymotemessage_read(message, buffer, ret);
				for (i = 0; i < DEVICEADAPTERTYPE_MAX; i++)
				{
					if (deviceadapter[i] != NULL)
					{
#ifdef FAST_PARSING
						if( deviceadapter_parse(deviceadapter[i], message) > 0 )
							break;
#else
						deviceadapter_parse(deviceadapter[i], message);
#endif
					}
				}
				anymotemessage_destroy(message);
			}
		}
	} while (ret > 0);
	close(serverfd);
	for (i = 0; i < DEVICEADAPTERTYPE_MAX; i++)
		if (deviceadapter[i]) deviceadapter_destroy(deviceadapter[i]);
	return 0;
}
