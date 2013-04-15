#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include <anymote/anymote.h>
#include <anymote/deviceadapter.h>

void anymotemessage_newbuilder(AnymoteMessage *this);
/*
void anymotemessage_build(AnymoteMessage *this, AnymoteMessage *message);
void anymotemessage_writeType(AnymoteMessage *this, int type);
void anymotemessage_writeUInt(AnymoteMessage *this, unsigned int value);
void anymotemessage_writeUShort(AnymoteMessage *this, unsigned short value);
*/
unsigned char *anymotemessage_readtype(AnymoteMessage *this, AnymoteTag *tag);
unsigned char *anymotemessage_readlen(AnymoteMessage *this, int *len);
unsigned char *anymotemessage_readbyte(AnymoteMessage *this, unsigned char *byte);
unsigned char *anymotemessage_readstring(AnymoteMessage *this, unsigned char *string, int stringlen);

#define anymotemessage_writeTag anymotemessage_writeUShort
void anymotemessage_writetype(AnymoteMessage *this, AnymoteTag value);
void anymotemessage_writelen(AnymoteMessage *this, int len);
void anymotemessage_writebyte(AnymoteMessage *this, unsigned char byte);
void anymotemessage_writestring(AnymoteMessage *this, unsigned char *string, int stringlen);

struct _AnymoteKeyEvent
{
	int m_type;
	unsigned int m_size;
	unsigned char *m_data;
	unsigned char *m_current;

	unsigned int m_unused_1:1;
	unsigned int m_unused_2: 1;
	unsigned int m_unused_3:1;
	unsigned int m_unused_4:1;
	unsigned int m_unused_5:1;
	unsigned int m_unused_6:1;
	unsigned int m_unused_7:1;
	unsigned int m_unused_8:1;
	unsigned int m_unused_9:1;
	unsigned int m_unused_10:1;
	unsigned int m_unused_12:1;

	long m_keycode;
	long m_action;
};

struct _AnymoteMouseEvent
{
	int m_type;
	unsigned int m_size;
	unsigned char *m_data;
	unsigned char *m_current;

	unsigned int m_unused_1:1;
	unsigned int m_unused_2:1;
	unsigned int m_unused_3:1;
	unsigned int m_unused_4:1;
	unsigned int m_unused_5:1;
	unsigned int m_unused_6:1;
	unsigned int m_unused_7:1;
	unsigned int m_unused_8:1;
	unsigned int m_unused_9:1;
	unsigned int m_unused_10:1;
	unsigned int m_unused_12:1;

	long m_xdelta;
	long m_ydelta;
};

struct _AnymoteMouseWheel
{
	int m_type;
	unsigned int m_size;
	unsigned char *m_data;
	unsigned char *m_current;
	unsigned int m_unused_1:1;
	unsigned int m_unused_2:1;
	unsigned int m_unused_3:1;
	unsigned int m_unused_4:1;
	unsigned int m_unused_5:1;
	unsigned int m_unused_6:1;
	unsigned int m_unused_7:1;
	unsigned int m_unused_8:1;
	unsigned int m_unused_9:1;
	unsigned int m_unused_10:1;
	unsigned int m_unused_12:1;

	long m_xscroll;
	long m_yscroll;
};

struct _AnymoteData
{
	int m_type;
	unsigned int m_size;
	unsigned char *m_data;
	unsigned char *m_current;
	unsigned int m_unused_1:1;
	unsigned int m_unused_2:1;
	unsigned int m_unused_3:1;
	unsigned int m_unused_4:1;
	unsigned int m_unused_5:1;
	unsigned int m_unused_6:1;
	unsigned int m_unused_7:1;
	unsigned int m_unused_8:1;
	unsigned int m_unused_9:1;
	unsigned int m_unused_10:1;
	unsigned int m_unused_12:1;

	unsigned char *m_datatype;
	unsigned char *m_datadata;
};

struct _AnymoteConnect
{
	int m_type;
	unsigned int m_size;
	unsigned char *m_data;
	unsigned char *m_current;
	unsigned int m_unused_1:1;
	unsigned int m_unused_2:1;
	unsigned int m_unused_3:1;
	unsigned int m_unused_4:1;
	unsigned int m_unused_5:1;
	unsigned int m_unused_6:1;
	unsigned int m_unused_7:1;
	unsigned int m_unused_8:1;
	unsigned int m_unused_9:1;
	unsigned int m_unused_10:1;
	unsigned int m_has_version:1;

	char *m_devicename;
	unsigned int m_version;
};

struct _AnymoteFling
{
	int m_type;
	unsigned int m_size;
	unsigned char *m_data;
	unsigned char *m_current;
	unsigned int m_unused_1:1;
	unsigned int m_unused_2:1;
	unsigned int m_unused_3:1;
	unsigned int m_unused_4:1;
	unsigned int m_unused_5:1;
	unsigned int m_unused_6:1;
	unsigned int m_unused_7:1;
	unsigned int m_unused_8:1;
	unsigned int m_unused_9:1;
	unsigned int m_unused_10:1;
	unsigned int m_has_version:1;

	char *m_uri;
};

struct _AnymoteRequestMessage
{
	int m_type;
	unsigned int m_size;
	unsigned char *m_data;
	unsigned char *m_current;

	unsigned int m_unused_1:1;
	unsigned int m_unused_2: 1;
	unsigned int m_unused_3:1;
	unsigned int m_unused_4:1;
	unsigned int m_has_keyEvent:1;
	unsigned int m_has_mouseEvent:1;
	unsigned int m_has_mouseWheel:1;
	unsigned int m_has_data:1;
	unsigned int m_has_connect:1;
	unsigned int m_has_fling:1;
	unsigned int m_has_version:1;

	struct _AnymoteKeyEvent *m_keyEvent;
	struct _AnymoteMouseEvent *m_mouseEvent;
	struct _AnymoteMouseWheel *m_mouseWheel;
	struct _AnymoteData *m_datamsg;
	struct _AnymoteConnect *m_connect;
	struct _AnymoteFling *m_fling;
};

struct _AnymoteResponseMessage
{
	int m_type;
	unsigned int m_size;
	unsigned char *m_data;
	unsigned char *m_current;
	unsigned int m_has_remMessage:1;
	unsigned int m_has_seqNum: 1;
	unsigned int m_has_reqMessage:1;
	unsigned int m_has_resMessage:1;
	unsigned int m_has_keyEvent:1;
	unsigned int m_has_mouseEvent:1;
	unsigned int m_has_mouseWheel:1;
	unsigned int m_has_data:1;
	unsigned int m_has_connect:1;
	unsigned int m_has_fling:1;
	unsigned int m_has_version:1;


};

struct _AnymoteRemoteMessage
{
	int m_type;
	unsigned int m_size;
	unsigned char *m_data;
	unsigned char *m_current;

	unsigned int m_unused_1:1;
	unsigned int m_has_seqNum: 1;
	unsigned int m_has_reqMessage:1;
	unsigned int m_has_resMessage:1;
	unsigned int m_unused_2:1;
	unsigned int m_unused_3:1;
	unsigned int m_unused_4:1;
	unsigned int m_unused_5:1;
	unsigned int m_unused_6:1;
	unsigned int m_unused_7:1;
	unsigned int m_unused_8:1;

	unsigned long m_seqNum;
	struct _AnymoteRequestMessage *m_reqMessage;
	struct _AnymoteResponseMessage *m_resMessage;
};

struct _AnymoteMessage
{
	int m_type;
	unsigned int m_size;
	unsigned char *m_data;
	unsigned char *m_current;

	unsigned int m_has_remMessage:1;
	unsigned int m_has_seqNum: 1;
	unsigned int m_has_reqMessage:1;
	unsigned int m_has_resMessage:1;
	unsigned int m_has_keyEvent:1;
	unsigned int m_has_mouseEvent:1;
	unsigned int m_has_mouseWheel:1;
	unsigned int m_has_data:1;
	unsigned int m_has_connect:1;
	unsigned int m_has_fling:1;
	unsigned int m_has_version:1;

	union {
		struct _AnymoteMessage *m_pointer;
		struct _AnymoteRemoteMessage *m_remMessage;
		unsigned long m_seqNum;
		struct _AnymoteRequestMessage *m_reqMessage;
		struct _AnymoteResponsMessage *m_respMessage;
		struct _AnymoteKeyEvent *m_keyEvent;
		struct _AnymoteMouseEvent *m_mouseEvent;
		struct _AnymoteMouseWheel *m_mouseWheel;
		struct _AnymoteData *m_datamsg;
		struct _AnymoteConnect *m_connect;
		struct _AnymoteFling *m_fling;
		unsigned long m_version;
		long m_xdleta;
		long m_ydelta;
	} m_message[6];
};

AnymoteMessage *anymotemessage_new(int type)
{
	AnymoteMessage *this = malloc(sizeof(AnymoteMessage));/* malloc check: free OK if  called*/
	memset(this, 0, sizeof( AnymoteMessage));
	this->m_type = type;
	return this;
}

void anymotemessage_destroy(AnymoteMessage *this)
{
	int i = 0;
	// AnymoteMessage is built recursivly
	if ( this->m_has_remMessage )
		anymotemessage_destroy(this->m_message[i].m_pointer);
	if (this->m_type == REMOTEMESSAGE)
	{
		if ( this->m_has_reqMessage)
			anymotemessage_destroy(this->m_message[1].m_pointer);
		if ( this->m_has_resMessage)
			anymotemessage_destroy(this->m_message[2].m_pointer);
	}
	if (this->m_type == REQUESTMESSAGE)
	{
		struct _AnymoteRequestMessage *_This = (struct _AnymoteRequestMessage *)this;
		if ( this->m_has_keyEvent )
			anymotemessage_destroy((AnymoteMessage *)_This->m_keyEvent);
		if ( this->m_has_mouseEvent )
			anymotemessage_destroy((AnymoteMessage *)_This->m_mouseEvent);
		if ( this->m_has_mouseWheel )
			anymotemessage_destroy((AnymoteMessage *)_This->m_mouseWheel);
		if ( this->m_has_data )
			anymotemessage_destroy((AnymoteMessage *)_This->m_datamsg);
		if ( this->m_has_connect )
			anymotemessage_destroy((AnymoteMessage *)_This->m_connect);
		if ( this->m_has_fling )
			anymotemessage_destroy((AnymoteMessage *)_This->m_fling);
	}
	if (this->m_type == RESPONSEMESSAGE)
	{
	}
	if (this->m_type == CONNECT)
	{
		struct _AnymoteConnect *_This =(struct _AnymoteConnect *)this;
		free(_This->m_devicename);
	}
	if (this->m_type == FLING)
	{
		struct _AnymoteFling *_This =(struct _AnymoteFling *)this;
		free(_This->m_uri);
	}
	if (this->m_type == REQDATA)
	{
		struct _AnymoteData *_This =(struct _AnymoteData *)this;
		free(_This->m_datatype);
		free(_This->m_datadata);
	}
	free(this);
}

/*
void anymotemessage_newbuilder(AnymoteMessage *this)
{
	this->m_size = 0;
	if ( this->m_data)
		free(this->m_data);
	this->m_data = malloc(ANYMOTEMESSAGE_DATA_DEFAULTSIZE);
}

void anymotemessage_build(AnymoteMessage *this, AnymoteMessage *message)
{
	switch(message->m_type)
	{
	case REMOTEMESSAGE: {
		anymotemessage_writetype(this, REMOTEMESSAGE);
		anymotemessage_build(this, message->m_message[0].m_remMessage);
	}
	break;
	case SEQNUM: {
		anymotemessage_writetype(this, SEQNUM);
		anymotemessage_writeUInt(this, message->m_message[0].m_seqNum);
	}
	break;
	case REQUESTMESSAGE: {
		// i am inside a RemoteMessage
		anymotemessage_writetype(this, REQUESTMESSAGE);
		anymotemessage_build(this, message->m_message[1].m_reqMessage);
	}
	if ( message->m_has_resMessage)
	{
		// i am inside a RemoteMessage
		anymotemessage_writetype(this, RESPONSEMESSAGE);
		anymotemessage_build(this, message->m_message[2].m_respMessage);
	}
	if ( message->m_has_keyEvent)
	{
		// i am inside a RequestMessage
		anymotemessage_writetype(this, KEYEVENT);
		{
			anymotemessage_writetype(this, KEYCODE);
			anymotemessage_writeUInt(this, message->m_message[0].m_keyEvent->m_keycode);
			anymotemessage_writetype(this, ACTION);
			anymotemessage_writeUInt(this, message->m_message[0].m_keyEvent->m_action);
		}
	}
	if ( message->m_has_mouseEvent)
	{
		anymotemessage_writeType(this, MOUSEEVENT);
		{
			anymotemessage_writetype(this, XDELTA);
			anymotemessage_writeUInt(this, message->m_message[1].m_mouseEvent->m_xdelta);
			anymotemessage_writetype(this, YDELTA);
			anymotemessage_writeUInt(this, message->m_message[1].m_mouseEvent->m_ydelta);
		}
	}
	if ( message->m_has_mouseWheel)
	{
		anymotemessage_writeType(this, MOUSEWHEEL);
		{
			anymotemessage_writetype(this, XAXIS);
			anymotemessage_writeUInt(this, message->m_message[2].m_mouseWheel->m_xaxis);
			anymotemessage_writetype(this, YAXIS);
			anymotemessage_writeUInt(this, message->m_message[2].m_mouseWheel->m_yaxis);
		}
	}
	if ( message->m_has_data)
	{
		// I am inside a	ResponseMessage or RemoteMessage
		anymotemessage_writeType(this, DATA);
		{
			anymotemessage_writetype(this, DATATYPE);
			anymotemessage_writestring(this, message->m_message[3].m_data->m_type);
			anymotemessage_writetype(this, DATADATA);
			anymotemessage_writestring(this, message->m_message[3].m_data->m_data);
		}
	}
	if ( message->m_has_connect)
	{
		anymotemessage_writetype(this, CONNECT);
		{
			anymotemessage_writetype(this, DEVICENAME);
			anymotemessage_writestring(this, message->m_message[4].m_connect->m_devicename);
		}
	}
	if ( message->m_has_fling)
	{
		anymotemessage_writetype(this, FLING);
		{
			anymotemessage_writetype(this, URI);
			anymotemessage_writestring(this, message->m_message[5].m_fling->m_uri);
		}
	}
	if ( message->m_has_flingResult)
	{
		// I am inside a	ResponseMessage
		anymotemessage_writetype(this, FLINGRESULT);
		anymotemessage_writestring(this, message->m_message[3]->m_result);
	}
	if ( message->m_has_version)
	{
		// I am inside a	Connect
		anymotemessage_writetype(this, VERSION);
		anymotemessage_writestring(this, (struct _AnymoteConnect *)message->m_version);
	}
}

void anymotemessage_writetype(AnymoteMessage *this, int type)
{
	void anymotemessage_writeTag(this, (type << 3) | 0x02)
}

void anymotemessage_writeUInt(AnymoteMessage *this, unsigned int value)
{
	if ( this->m_cursor - this->m_data + sizeof(unsigned int) > this->m_size)
	{
		this->m_data = realloc(this->m_data, this->m_size + ANYMOTEMESSAGE_DATA_DEFAULTSIZE);
		if (this->m_data)
			this->m_size+=ANYMOTEMESSAGE_DATA_DEFAULTSIZE;
		else
			return;
	}
	*(unsigned int*)this->m_cursor = value;
	this->m_cursor += sizeof(unsigned int);
}

void anymotemessage_writeUShort(AnymoteMessage *this, unsigned short value)
{
	if ( this->m_cursor - this->m_data + sizeof(unsigned short) > this->m_size)
	{
		this->m_data = realloc(this->m_data, this->m_size + ANYMOTEMESSAGE_DATA_DEFAULTSIZE);
		if (this->m_data)
			this->m_size+=ANYMOTEMESSAGE_DATA_DEFAULTSIZE;
		else
			return;
	}
	*(unsigned short*)this->m_cursor = value;
	this->m_cursor += sizeof(unsigned short);
}
*/
unsigned char *anymotemessage_read(AnymoteMessage *this, unsigned char *buffer, unsigned long bufferlen)
{
	int len = 0;
	// if this->m_data is not null a "newbuilder" was used and not free
	if (this->m_data)
		free(this->m_data);
	this->m_size = bufferlen;
	this->m_data = buffer;
	this->m_current = buffer;
	this->m_current = anymotemessage_readlen(this, &len);
	if (this->m_size < len)
		goto error;
	while(this->m_current - this->m_data < len)
	{
		AnymoteTag tag;
		this->m_current = anymotemessage_readtype(this, &tag);
		switch(tag)
		{
			case REMOTEMESSAGE: {
				log("I am a %s\n", "REMOTEMESSAGE");
				AnymoteMessage *_This =(AnymoteMessage *)this;
				_This->m_has_remMessage &= 0x01;
				struct _AnymoteRemoteMessage * message = (struct _AnymoteRemoteMessage * )anymotemessage_new(REMOTEMESSAGE);
				_This->m_message[0].m_remMessage = message;
				this->m_current = anymotemessage_read((AnymoteMessage *)message, this->m_current, this->m_size - (this->m_current - this->m_data));
				if (_This->m_message[0].m_remMessage->m_has_seqNum)
					anymotemessage_print(this);
			}
			break;
			case SEQNUM: {
				struct _AnymoteRemoteMessage *_This =(struct _AnymoteRemoteMessage *)this;
				_This->m_has_seqNum |= 0x01;
				this->m_current = anymotemessage_readbyte(this, (unsigned char *)&_This->m_seqNum);
			}
			break;
			case REQUESTMESSAGE: {
				struct _AnymoteRemoteMessage *_This =(struct _AnymoteRemoteMessage *)this;
				_This->m_has_reqMessage |= 0x01;
				struct _AnymoteRequestMessage * message = (struct _AnymoteRequestMessage *)anymotemessage_new(REQUESTMESSAGE);
				_This->m_reqMessage = message;
				this->m_current = anymotemessage_read((AnymoteMessage *)message, this->m_current, this->m_size - (this->m_current - this->m_data));
			}
			break;
			case RESPONSEMESSAGE: {
				struct _AnymoteRemoteMessage *_This =(struct _AnymoteRemoteMessage *)this;
				_This->m_has_reqMessage |= 0x01;
				struct _AnymoteResponseMessage * message = (struct _AnymoteResponseMessage *)anymotemessage_new(RESPONSEMESSAGE);
				_This->m_resMessage = message;
				this->m_current = anymotemessage_read((AnymoteMessage *)message, this->m_current, this->m_size - (this->m_current - this->m_data));
			}
			break;
			case KEYEVENT: {
				struct _AnymoteRequestMessage *_This =(struct _AnymoteRequestMessage *)this;
				_This->m_has_keyEvent |= 0x01;
				struct _AnymoteKeyEvent * message = (struct _AnymoteKeyEvent *)anymotemessage_new(KEYEVENT);
				_This->m_keyEvent = message;
				this->m_current = anymotemessage_read((AnymoteMessage *)message, this->m_current, this->m_size - (this->m_current - this->m_data));
			}
			break;
			case MOUSEEVENT: {
				struct _AnymoteRequestMessage *_This =(struct _AnymoteRequestMessage *)this;
				_This->m_has_mouseEvent |= 0x01;
				struct _AnymoteMouseEvent * message = (struct _AnymoteMouseEvent *)anymotemessage_new(MOUSEEVENT);
				_This->m_mouseEvent = message;
				this->m_current = anymotemessage_read((AnymoteMessage *)message, this->m_current, this->m_size - (this->m_current - this->m_data));
			}
			break;
			case MOUSEWHEEL: {
				struct _AnymoteRequestMessage *_This =(struct _AnymoteRequestMessage *)this;
				_This->m_has_mouseWheel |= 0x01;
				struct _AnymoteMouseWheel * message = (struct _AnymoteMouseWheel *)anymotemessage_new(MOUSEWHEEL);
				_This->m_mouseWheel = message;
				this->m_current = anymotemessage_read((AnymoteMessage *)message, this->m_current, this->m_size - (this->m_current - this->m_data));
			}
			break;
			case REQDATA: {
				log("I am a %s %X\n", "REQDATA", REQDATA);
				struct _AnymoteRequestMessage *_This =(struct _AnymoteRequestMessage *)this;
				_This->m_has_data |= 0x01;
				struct _AnymoteData * message = (struct _AnymoteData *)anymotemessage_new(REQDATA);
				_This->m_datamsg = message;
				this->m_current = anymotemessage_read((AnymoteMessage *)message, this->m_current, this->m_size - (this->m_current - this->m_data));
			}
			break;
			case CONNECT: {
				log("I am a %s %X\n", "CONNECT", CONNECT);
				struct _AnymoteRequestMessage *_This =(struct _AnymoteRequestMessage *)this;
				_This->m_has_connect |= 0x01;
				struct _AnymoteConnect * message = (struct _AnymoteConnect *)anymotemessage_new(CONNECT);
				_This->m_connect = message;
				this->m_current = anymotemessage_read((AnymoteMessage *)message, this->m_current, this->m_size - (this->m_current - this->m_data));
			}
			break;
			case FLING: {
				log("I am a %s %X\n", "FLING", FLING);
				struct _AnymoteRequestMessage *_This =(struct _AnymoteRequestMessage *)this;
				_This->m_has_fling |= 0x01;
				struct _AnymoteFling * message = (struct _AnymoteFling *)anymotemessage_new(FLING);
				_This->m_fling = message;
				this->m_current = anymotemessage_read((AnymoteMessage *)message, this->m_current, this->m_size - (this->m_current - this->m_data));
			}
			break;
			case KEYCODE: {
				struct _AnymoteKeyEvent *_This =(struct _AnymoteKeyEvent *)this;
				this->m_current = anymotemessage_readbyte(this, (unsigned char *)&_This->m_keycode);
				if (_This->m_keycode > 0x7F)
				{
					unsigned char tempo;
					this->m_current = anymotemessage_readbyte(this, &tempo);
					_This->m_keycode |= (((int)tempo) << 8) & 0xFF00;
				}
			}
			break;
			case ACTION: {
				struct _AnymoteKeyEvent *_This =(struct _AnymoteKeyEvent *)this;
				this->m_current = anymotemessage_readbyte(this, (unsigned char *)&_This->m_action);
			}
			break;
			case XDELTA: {
				struct _AnymoteMouseEvent *_This =(struct _AnymoteMouseEvent *)this;
				this->m_current = anymotemessage_readbyte(this, (unsigned char *)&_This->m_xdelta);
				if (((char)_This->m_xdelta & 0x80))
				{
					unsigned char tempo;
					do
					{
						this->m_current = anymotemessage_readbyte(this, &tempo);
					} while (tempo == 0xFF);
					_This->m_xdelta += 0xFFFFFF00;
				}
			}
			break;
			case YDELTA: {
				struct _AnymoteMouseEvent *_This =(struct _AnymoteMouseEvent *)this;
				this->m_current = anymotemessage_readbyte(this, (unsigned char *)&_This->m_ydelta);
				if (((char)_This->m_ydelta & 0x80))
				{
					unsigned char tempo;
					do
					{
						this->m_current = anymotemessage_readbyte(this, &tempo);
					} while (tempo == 0xFF);
					_This->m_ydelta += 0xFFFFFF00;
				}
			}
			break;
			case XSCROLL: {
				struct _AnymoteMouseWheel *_This =(struct _AnymoteMouseWheel *)this;
				this->m_current = anymotemessage_readbyte(this, (unsigned char *)&_This->m_xscroll);
				if (((char)_This->m_xscroll & 0x80))
				{
					unsigned char tempo;
					do
					{
						this->m_current = anymotemessage_readbyte(this, &tempo);
					} while (tempo == 0xFF);
					_This->m_xscroll += 0xFFFFFF00;
				}
			}
			break;
			case YSCROLL: {
				struct _AnymoteMouseWheel *_This =(struct _AnymoteMouseWheel *)this;
				this->m_current = anymotemessage_readbyte(this, (unsigned char *)&_This->m_yscroll);
				if (((char)_This->m_yscroll & 0x80))
				{
					unsigned char tempo;
					do
					{
						this->m_current = anymotemessage_readbyte(this, &tempo);
					} while (tempo == 0xFF);
					_This->m_yscroll += 0xFFFFFF00;
				}
			}
			break;
			case DEVICENAME: {
				struct _AnymoteConnect *_This =(struct _AnymoteConnect *)this;
				_This->m_devicename = (char *) malloc(256);
				memset(_This->m_devicename, 0, 256);
				this->m_current = anymotemessage_readstring(this, (unsigned char *)_This->m_devicename, 255);
			}
			break;
			case VERSION: {
				struct _AnymoteConnect *_This =(struct _AnymoteConnect *)this;
				_This->m_has_version |= 0x01;
				this->m_current = anymotemessage_readbyte(this, (unsigned char *)&_This->m_version);
			}
			break;
			case URI: {
				struct _AnymoteFling *_This =(struct _AnymoteFling *)this;
				_This->m_uri = (char *) malloc(256);
				memset(_This->m_uri, 0, 256);
				this->m_current = anymotemessage_readstring(this, (unsigned char *)_This->m_uri, 255);
			}
			break;
			case DATATYPE: {
				struct _AnymoteData *_This =(struct _AnymoteData *)this;
				_This->m_datatype = (unsigned char *) malloc(256);
				memset(_This->m_datatype, 0, 256);
				this->m_current = anymotemessage_readstring(this, _This->m_datatype, 255);
			}
			break;
			case DATADATA: {
				struct _AnymoteData *_This =(struct _AnymoteData *)this;
				_This->m_datadata = (unsigned char *) malloc(256);
				memset(_This->m_datadata, 0, 256);
				this->m_current = anymotemessage_readstring(this, _This->m_datadata, 255);
			}
			break;
/*
			case FLINGRESULT: {
			}
			break;
*/
			default: {
				int i;
				log("AnymoteMessage unknown tag %X\n", tag);
				for (i = 0; i < bufferlen; i++)
					log("%02X ", buffer[i]);
				//~ for (this->m_current; this->m_size - (this->m_current - this->m_data) > 0; this->m_current++)
					//~ printf("%02X ", *this->m_current);
				log("\n");
				this->m_current = buffer + bufferlen;
			}
			break;
		}
	}
	this->m_data = NULL;
	return this->m_current;
error:
	return NULL;
}

unsigned char *anymotemessage_readtype(AnymoteMessage *this, AnymoteTag *tag)
{
	unsigned char *buffer = this->m_current;
	if (buffer == NULL)
		return NULL;
	*tag = (int)(this->m_type << 3) & 0xFFFFFFFF;
	*tag |= ((*(AnymoteTag *)buffer) >> 3 & 0x07);
	buffer += 1;
	return buffer;
}

unsigned char *anymotemessage_readlen(AnymoteMessage *this, int *len)
{
	return anymotemessage_readbyte(this, (unsigned char *)len);
}

unsigned char *anymotemessage_readbyte(AnymoteMessage *this, unsigned char *byte)
{
	unsigned char *buffer = this->m_current;
	if (buffer == NULL)
		return NULL;
	*byte = *buffer;
	buffer += 1;
	return buffer;
}

unsigned char *anymotemessage_readstring(AnymoteMessage *this, unsigned char *string, int stringlen)
{
	char *buffer = (char *)this->m_current;
	int len;
	if (buffer == NULL)
		return NULL;
	len = (int)(*buffer & 0xFF);
	if (len + 1 > stringlen)
		return NULL;
	buffer++;
	strncpy((char *)string, buffer, len);
	string[len] = 0;
	if (*buffer == 0)
		buffer++;
	return (unsigned char *)buffer + len;
}

int anymotemessage_getsequence(AnymoteMessage *this)
{
	int sequence = 0;
	if (this->m_has_remMessage)
		sequence = anymotemessage_getsequence((AnymoteMessage *)this->m_message[0].m_remMessage);
	if (this->m_has_seqNum && this->m_type == REMOTEMESSAGE)
	{
		struct _AnymoteRemoteMessage *_This = (struct _AnymoteRemoteMessage *)this;
		sequence = _This->m_seqNum;
	}
	return sequence;
}

DeviceAdapter_Event *anymotemessage_getevent(AnymoteMessage *this)
{
	DeviceAdapter_Event *event = NULL;
	if (this->m_has_remMessage)
		event = anymotemessage_getevent((AnymoteMessage *)this->m_message[0].m_remMessage);
	if (this->m_has_reqMessage && this->m_type == REMOTEMESSAGE)
		event = anymotemessage_getevent((AnymoteMessage *)((struct _AnymoteRemoteMessage *)this)->m_reqMessage);
	if (this->m_has_keyEvent && this->m_type == REQUESTMESSAGE)
		event = anymotemessage_getevent((AnymoteMessage *)((struct _AnymoteRequestMessage *)this)->m_keyEvent);
	if (this->m_has_mouseEvent && this->m_type == REQUESTMESSAGE)
		event = anymotemessage_getevent((AnymoteMessage *)((struct _AnymoteRequestMessage *)this)->m_mouseEvent);
	if (this->m_has_mouseWheel && this->m_type == REQUESTMESSAGE)
		event = anymotemessage_getevent((AnymoteMessage *)((struct _AnymoteRequestMessage *)this)->m_mouseWheel);
	if (this->m_type == KEYEVENT)
	{
		struct _AnymoteKeyEvent *_This = (struct _AnymoteKeyEvent *)this;

		event = malloc(sizeof(DeviceAdapter_Event)); /* malloc check: free OK if caller destroy it! free called by deviceadaptermouse_parse and deviceadapterkbd_parse*/
		event->m_type = EVENTTYPE_KEYEVENT;
		event->m_keyevent.m_keycode = _This->m_keycode;
		event->m_keyevent.m_action = _This->m_action;
	}
	if (this->m_type == MOUSEEVENT)
	{
		struct _AnymoteMouseEvent *_This = (struct _AnymoteMouseEvent *)this;

		event = malloc(sizeof(DeviceAdapter_Event));/* malloc check: free OK if caller destroy it! free called by deviceadaptermouse_parse and deviceadapterkbd_parse*/
		event->m_type = EVENTTYPE_MOUSEEVENT;
		event->m_mouseevent.m_xdelta = _This->m_xdelta;
		event->m_mouseevent.m_ydelta = _This->m_ydelta;
	}

	if (this->m_type == MOUSEWHEEL)
	{
		struct _AnymoteMouseWheel *_This = (struct _AnymoteMouseWheel *)this;

		event = malloc(sizeof(DeviceAdapter_Event));/* malloc check: free OK if caller destroy it! free called by deviceadaptermouse_parse and deviceadapterkbd_parse*/
		event->m_type = EVENTTYPE_MOUSEWHEEL;
		event->m_mousewheel.m_xscroll = _This->m_xscroll;
		event->m_mousewheel.m_yscroll = _This->m_yscroll;
	}

	return event;
}

char *anymotemessage_getdevicename(AnymoteMessage *this)
{
	char *name = NULL;
	if (this->m_has_remMessage)
		name = anymotemessage_getdevicename((AnymoteMessage *)this->m_message[0].m_remMessage);
	if (this->m_has_reqMessage && this->m_type == REMOTEMESSAGE)
		name = anymotemessage_getdevicename((AnymoteMessage *)((struct _AnymoteRemoteMessage *)this)->m_reqMessage);
	if (this->m_has_connect && this->m_type == REQUESTMESSAGE)
		name = anymotemessage_getdevicename((AnymoteMessage *)((struct _AnymoteRequestMessage *)this)->m_connect);
	if (this->m_type == CONNECT)
	{
		struct _AnymoteConnect *_This = (struct _AnymoteConnect *)this;

		name = malloc(strlen(_This->m_devicename) + 1);/* malloc check: free OK if caller destroy it! free called by deviceadapter_parse*/
		strcpy(name, _This->m_devicename);
	}

	return name;
}

char *anymotemessage_getdata(AnymoteMessage *this, DeviceAdapter_DataType *type)
{
	char *data = NULL;
	if (this->m_has_remMessage)
		data = anymotemessage_getdata((AnymoteMessage *)this->m_message[0].m_remMessage, type);
	if (this->m_has_reqMessage && this->m_type == REMOTEMESSAGE)
		data = anymotemessage_getdata((AnymoteMessage *)((struct _AnymoteRemoteMessage *)this)->m_reqMessage, type);
	if (this->m_has_data && this->m_type == REQUESTMESSAGE)
		data = anymotemessage_getdata((AnymoteMessage *)((struct _AnymoteRequestMessage *)this)->m_datamsg, type);
	if (this->m_type == REQDATA)
	{
		struct _AnymoteData *_This = (struct _AnymoteData *)this;

		if ((char*)strstr((char *)_This->m_datatype, "string") != ((char*)NULL))
		{
			int len = strlen( (char *)_This->m_datadata);
			*type = DATATYPE_STRING;
			data = malloc(len + 1);
			memset(data, 0, len);
			// I don't know why but in some cases len =1 _This->m_datadata="f" and the function return data="f?? oid"
			strncpy(data, ((char *)(_This->m_datadata)), len);
			data[len] = 0;
		}
	}

	return data;
}

void anymotemessage_printremotemessage(struct _AnymoteRemoteMessage *this)
{
	printf("Remote:\n");
	if (this->m_has_seqNum)
		printf("SeqNum: %lu\n", this->m_seqNum);
	if (this->m_has_reqMessage)
		anymotemessage_print((AnymoteMessage *)this->m_reqMessage);
	if (this->m_has_resMessage)
		anymotemessage_print((AnymoteMessage *)this->m_resMessage);
}

void anymotemessage_printrequestmessage(struct _AnymoteRequestMessage *this)
{
	char found_one = 0;
	printf("Request:\n");
	if (this->m_has_keyEvent)
	{
		found_one = 1;
		anymotemessage_print((AnymoteMessage *)this->m_keyEvent);
	}
	if (this->m_has_mouseEvent)
	{
		found_one = 1;
		anymotemessage_print((AnymoteMessage *)this->m_mouseEvent);
	}
	if (this->m_has_mouseWheel)
	{
		found_one = 1;
		anymotemessage_print((AnymoteMessage *)this->m_mouseWheel);
	}
	if (this->m_has_data)
	{
		found_one = 1;
		anymotemessage_print((AnymoteMessage *)this->m_datamsg);
	}
	if (this->m_has_connect)
	{
		found_one = 1;
		anymotemessage_print((AnymoteMessage *)this->m_connect);
	}
	if (this->m_has_fling)
	{
		found_one = 1;
		anymotemessage_print((AnymoteMessage *)this->m_fling);
	}
	if (found_one == 0)
		printf(" Empty\n");

}

void anymotemessage_printkeyevent(struct _AnymoteKeyEvent *this)
{
	printf("KeyEvent:\n");
	printf(" Key 0x%lX %ld %s\n", this->m_keycode, this->m_keycode, this->m_action?"DOWN":"UP");
}

void anymotemessage_printmouseevent(struct _AnymoteMouseEvent *this)
{
	printf("MouseEvent:\n");
	printf(" Move %d %d\n", (char)this->m_xdelta, (char)this->m_ydelta);
}

void anymotemessage_printmousewheel(struct _AnymoteMouseWheel *this)
{
	printf("MouseWheel:\n");
	printf(" Move %d %d\n", (char)this->m_xscroll, (char)this->m_yscroll);
}

void anymotemessage_printconnect(struct _AnymoteConnect *this)
{
	if (this->m_has_version)
		printf("Connect: name %s %d\n", this->m_devicename, this->m_version);
	else
		printf("Connect: name %s\n", this->m_devicename);
}

void anymotemessage_printdata(struct _AnymoteData *this)
{
	printf("Data: \n");
	printf("type %s\n", this->m_datatype);
	printf("data %s\n", this->m_datadata);
}

void anymotemessage_printfling(struct _AnymoteFling *this)
{
	printf("Fling: \n");
	printf("uri %s\n", this->m_uri);
}

void anymotemessage_printresponsemessage(struct _AnymoteResponseMessage *this)
{
	printf("Response\n");
}

void anymotemessage_print(AnymoteMessage *this)
{
	if (this == NULL)
	{
		printf("NULL message\n");
		return;
	}
	if (this->m_has_remMessage)
		anymotemessage_print((AnymoteMessage *)this->m_message[0].m_remMessage);
	else if (this->m_type == REMOTEMESSAGE)
		anymotemessage_printremotemessage((struct _AnymoteRemoteMessage *)this);
	else if (this->m_type == REQUESTMESSAGE)
		anymotemessage_printrequestmessage((struct _AnymoteRequestMessage *)this);
	else if (this->m_type == RESPONSEMESSAGE)
		anymotemessage_printresponsemessage((struct _AnymoteResponseMessage *)this);
	else if (this->m_type == KEYEVENT)
		anymotemessage_printkeyevent((struct _AnymoteKeyEvent *)this);
	else if (this->m_type == MOUSEEVENT)
		anymotemessage_printmouseevent((struct _AnymoteMouseEvent *)this);
	else if (this->m_type == MOUSEWHEEL)
		anymotemessage_printmousewheel((struct _AnymoteMouseWheel *)this);
	else if (this->m_type == FLING)
		anymotemessage_printfling((struct _AnymoteFling *)this);
	else if (this->m_type == CONNECT)
		anymotemessage_printconnect((struct _AnymoteConnect *)this);
	else if (this->m_type == REQDATA)
		anymotemessage_printdata((struct _AnymoteData *)this);
	else
		printf("message unknown type %d\n", this->m_type);
}

