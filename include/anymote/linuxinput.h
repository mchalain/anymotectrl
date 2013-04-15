#ifndef __LINUXINPUT_H__
#define __LINUXINPUT_H__

#include <linux/input.h>

#include "deviceadapter.h"

#define EVENT_BUFFER_LEN sizeof(struct input_event)

struct _LinuxInputEvent;
typedef struct _LinuxInputEvent LinuxInputEvent;

LinuxInputEvent * linuxinputevent_new(DeviceAdapter_Event *event);
void linuxinputevent_destroy(LinuxInputEvent *this);
int linuxinputevent_copy(LinuxInputEvent *this, unsigned char *buffer, int len);
int linuxinputevent_end(LinuxInputEvent *this);

#endif