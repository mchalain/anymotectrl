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
#include <anymote/devicedriver.h>
#include <anymote/linuxinput.h>

#define DEVICEPATH "/dev/input"

#ifdef FUSD
typedef struct fusd_file_info devicefile_info
typedef struct fusd_file_operations DeviceFile_Operations;
#else
typedef void devicefile_info;

struct _devicefile_operations
{
	int (*open)(devicefile_info *);
	int (*read)(devicefile_info *, char *buf, size_t len, loff_t *ofs);
	int (*close)(devicefile_info*);
};
typedef struct _devicefile_operations DeviceFile_Operations;
#endif

int da_open(devicefile_info *file);
int da_close(devicefile_info *file);
int da_read(devicefile_info *file, char  *buf, size_t len, loff_t *ofs);

DeviceFile_Operations g_fops =
{
	open: da_open,
	close: da_close,
	read: da_read,
};

int da_open(devicefile_info *file)
{
	return -1;
}
int da_close(devicefile_info *file)
{
	return -1;
}
int da_read(devicefile_info *file, char  *buf, size_t len, loff_t *ofs)
{
	return -1;
}

struct _DeviceDriver
{
	unsigned char m_connected:1;

	char *m_name;
	char *m_path;
	DeviceFile_Operations *m_fops;
	int m_devicefd;
};

DeviceDriver *devicedriver_new(char *devicepath)
{
	DeviceDriver *this = malloc(sizeof(DeviceDriver)); /* malloc check: free OK if devicedriver_destroy called */
	memset(this, 0, sizeof(DeviceDriver));
	if (devicepath)
	{
		this->m_path = malloc(strlen(devicepath) + 1);/* malloc check: free OK if devicedriver_destroy called */
		strcpy(this->m_path, devicepath);
	}
	else
	{
		this->m_path = malloc(strlen(DEVICEPATH) +1);/* malloc check: free OK if devicedriver_destroy called */
		strcpy(this->m_path, DEVICEPATH);
	}
	this->m_fops = &g_fops;
	return this;
}

void devicedriver_destroy(DeviceDriver *this)
{
	free(this->m_path);
	if (this->m_name)
		free(this->m_name);
	free(this);
}

int devicedriver_create(DeviceDriver *this, char *devicename)
{
	char *path;
	struct stat filestatus;


	this->m_name = malloc(len + 1);/* malloc check: free OK if devicedriver_destroy called */
	memset(this->m_name, 0, len + 1);
	strcpy(this->m_name, devicename);

	this->m_connected |= 0x01;

	stat(this->m_path, &filestatus);
	if ( S_ISDIR(filestatus.st_mode))
	{
		// len = strlen(devicename) = strlen(this->m_name);
		path = malloc(strlen(this->m_path) + len + 2);/* malloc check: free OK */
		sprintf(path, "%s/%s", this->m_path, this->m_name);
#ifdef FUSD
		int fds[2];
		fusd_register(path, 0666, (void *)this, this->m_fops);
		pipe(fds);
		if (fork() == 0)
		{
			this->m_devicefd = fds[1];
			close(fds[0]);
			fusd_run();
			exit(0);
		}
		else
		{
			this->m_devicefd = fds[0];
			close(fds[1]);
		}
#else
		mkfifo(path, 0666);
		log("device open %s\n", __FUNCTION__, path);
		this->m_devicefd = open(path, O_RDWR | O_NONBLOCK);
		if (this->m_devicefd == -1)
			log("error to open %ld : %s\n", errno, strerror(errno));
#endif
		free(path);
	}
	else
	{
		path = this->m_path;
		log("device open %s\n", path);
		this->m_devicefd = open(path, O_WRONLY | O_NONBLOCK);
		if (this->m_devicefd == -1)
			fprintf(stderr, "error to open %s: (%ld) %s\n", path, errno, strerror(errno));
	}
}


int devicedriver_write(DeviceDriver *this, unsigned char *buffer, int len)
{
	int ret = -1;
	ret = write(this->m_devicefd, buffer, len);
	return ret;
}

