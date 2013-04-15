#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>

#include "linuxinput.h"
#include "deviceadapter.h"

#define LINUXINPUTEVENT_MAXEVENTS 10
#ifndef _INPUT_H
struct input_event {
	struct timeval time;
	__u16 type;
	__u16 code;
	__s32 value;
};
#endif

static int linuxinputevent_createsyncevent(LinuxInputEvent *this);
static int linuxinputevent_createlinuxevent(LinuxInputEvent *this, unsigned short type, unsigned short code, long value);
static int linuxinputevent_createkeyevent(LinuxInputEvent *this, DeviceAdapter_KeyEvent *keyevent);
static int linuxinputevent_createmouseevent(LinuxInputEvent *this, DeviceAdapter_MouseEvent *event);

struct _LinuxInputEvent
{
	struct input_event *m_event[LINUXINPUTEVENT_MAXEVENTS];
	int m_nbevents;
	int m_current;
};

LinuxInputEvent * linuxinputevent_new(DeviceAdapter_Event *event)
{
	LinuxInputEvent *this = malloc(sizeof(LinuxInputEvent));/* malloc check: free OK if linuxinputevent_destroy called*/
	memset(this, 0, sizeof(LinuxInputEvent));
	switch(event->m_type)
	{
		case EVENTTYPE_KEYEVENT:
			linuxinputevent_createkeyevent(this, &event->m_keyevent);
		break;
		case EVENTTYPE_MOUSEEVENT:
			linuxinputevent_createmouseevent(this, &event->m_mouseevent);
		break;
		default:
		break;
	}
	return this;
}

void linuxinputevent_destroy(LinuxInputEvent *this)
{
	while (this->m_nbevents > this->m_current)
	{
		linuxinputevent_end(this);
	}
	free(this);
}

#define KEYPRESS 1
#define KEYRELEASE 0
int linuxinputevent_createkeyevent(LinuxInputEvent *this, DeviceAdapter_KeyEvent *keyevent)
{
	int ret = 0;
	if (keyevent->m_action == KEYACTION_DOWNUP)
	{
		keyevent->m_action = KEYACTION_DOWN;
		ret = linuxinputevent_createkeyevent(this, keyevent);
		keyevent->m_action = KEYACTION_UP;
		ret = linuxinputevent_createkeyevent(this, keyevent);
	}
	else
	{
		if (keyevent->m_keycode == 0)
		{
			return -1;
		}
		ret = linuxinputevent_createlinuxevent(this, EV_MSC, MSC_SCAN, keyevent->m_keycode);
		if (keyevent->m_action == KEYACTION_DOWN)
			ret = linuxinputevent_createlinuxevent(this, EV_KEY, keyevent->m_keycode, KEYPRESS);
		else if (keyevent->m_action == KEYACTION_UP)
			ret = linuxinputevent_createlinuxevent(this, EV_KEY, keyevent->m_keycode, KEYRELEASE);
		linuxinputevent_createsyncevent(this);
	}

	return ret;
}

int linuxinputevent_createmouseevent(LinuxInputEvent *this, DeviceAdapter_MouseEvent *event)
{
	int ret = 0;

	if (event->m_xdelta)
	{
		ret = linuxinputevent_createlinuxevent(this, EV_REL, REL_X, event->m_xdelta);
		linuxinputevent_createsyncevent(this);
	}

	if (event->m_ydelta)
	{
		ret = linuxinputevent_createlinuxevent(this, EV_REL, REL_Y, event->m_ydelta);
		linuxinputevent_createsyncevent(this);
	}

	return ret;
}

int linuxinputevent_createmousewheel(LinuxInputEvent *this, DeviceAdapter_MouseWheel *event)
{
	int ret = 0;
	if (event->m_xscroll)
	{
		ret = linuxinputevent_createlinuxevent(this, EV_REL, REL_WHEEL, event->m_xscroll);
		linuxinputevent_createsyncevent(this);
	}

	if (event->m_yscroll)
	{
		ret = linuxinputevent_createlinuxevent(this, EV_REL, REL_HWHEEL, event->m_yscroll);
		linuxinputevent_createsyncevent(this);
	}

	return ret;
}

int linuxinputevent_createsyncevent(LinuxInputEvent *this)
{
	return linuxinputevent_createlinuxevent(this, EV_SYN, SYN_REPORT, 0);
}

int linuxinputevent_createlinuxevent(LinuxInputEvent *this, unsigned short type, unsigned short code, long value)
{
	int i = this->m_nbevents;
	struct timeval time;
	gettimeofday(&time, NULL);

	if ( i > LINUXINPUTEVENT_MAXEVENTS)
	{
		fprintf(stderr, "%s: error Max events defined\n", __FUNCTION__);
		return -1;
	}
	this->m_event[i] = malloc(sizeof(struct input_event));/* malloc check: free OK if linuxinputevent_end or linuxinputevent_destroy called*/
	this->m_event[i]->time = time;
	this->m_event[i]->type = type;
	this->m_event[i]->code = code;
	this->m_event[i]->value = value;

	this->m_nbevents = ++i;
	return 0;
}

int linuxinputevent_copy(LinuxInputEvent *this, unsigned char *buffer, int len)
{
	if (this->m_nbevents > this->m_current)
	{
		if (len > sizeof(struct input_event))
			len = sizeof(struct input_event);
		memcpy(buffer, this->m_event[this->m_current], len);
	}
	return len;
}

int linuxinputevent_end(LinuxInputEvent *this)
{
	if (this->m_nbevents > this->m_current)
	{
		if (this->m_event[this->m_current])
			free(this->m_event[this->m_current]);
		this->m_event[this->m_current] = NULL;
		this->m_current++;
	}
	return (this->m_nbevents - this->m_current);
}
