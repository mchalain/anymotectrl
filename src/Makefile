MAIN_TARGET=anymotectrld
MAIN_SRCS=main.c

DEVICEADAPTERS=kbd mouse remote

LIB_TARGET=anymotectrl
LIB_SRCS= anymote.c deviceadapter.c  linuxinput.c devicedriver.c  deviceadapterfactory.c

LIBDEVICEDRIVER_TARGET= devicedriver_uinput
LIBDEVICEDRIVER_SRCS=devicedriver_uinput.c

TARGETDIR?=../bin
OBJDIR?=obj
PREFIX?=/usr/local
SHAREDIR?=$(PREFIX)/share/anymote
BINDIR?=$(PREFIX)/bin
LIBDIR?=$(PREFIX)/lib
CONFIGDIR?=$(PREFIX)/etc

MKDIR=mkdir
CP=cp
ifneq ($(origin ARCH), undefined)
	export CC:=$(ARCH)gcc
	export LD:=$(ARCH)$(LD)
	export AR:=$(ARCH)$(AR)
	OBJDIR:=$(ARCH)$(OBJDIR)
	TARGETDIR:=../$(ARCH)bin
	CFLAGS+= -DBROADCOM
endif

CFLAGS=-g -Wall
#LDFLAGS= -lefence -lpthread

all: $(TARGETDIR)/$(MAIN_TARGET) $(DEVICEADAPTERS)

static: CFLAGS+= -DSTATIC

CFLAGS+= -I../include
CFLAGS+=  -DSHAREDIR=\"$(SHAREDIR)\" -DCONFIGDIR=\"$(CONFIGDIR)\"

LIBDEVICEADAPTER_TARGET:= deviceadapter_

MAIN_OBJS:=$(addprefix $(OBJDIR)/, $(patsubst  %.c,%.o, $(MAIN_SRCS)))
LIB_OBJS:=$(addprefix $(OBJDIR)/, $(patsubst  %.c,%.o, $(LIB_SRCS)))

LIBDEVICEDRIVER_OBJS:=$(addprefix $(OBJDIR)/, $(patsubst  %.c,%.o, $(LIBDEVICEDRIVER_SRCS)))
LIBDEVICEDRIVER:=lib$(LIBDEVICEDRIVER_TARGET).so

$(MAIN_OBJS): |$(OBJDIR) $(TARGETDIR)

$(OBJDIR) $(TARGETDIR):
	$(MKDIR) $@

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(TARGETDIR)/lib$(LIB_TARGET).so: CFLAGS+=-fPIC
$(TARGETDIR)/lib$(LIB_TARGET).so: $(LIB_OBJS)
	$(LD) -shared -fPIC -o $@ $^

$(OBJDIR)/lib$(LIB_TARGET).a: $(LIB_OBJS)
	$(AR) rcs $@ $^

.SECONDEXPANSION:
$(DEVICEADAPTERS): $$(TARGETDIR)/lib$$(LIBDEVICEADAPTER_TARGET)$$@.so

$(TARGETDIR)/lib$(LIBDEVICEADAPTER_TARGET)%.so: CFLAGS+=-fPIC
$(TARGETDIR)/lib$(LIBDEVICEADAPTER_TARGET)%.so: $(OBJDIR)/$(LIBDEVICEADAPTER_TARGET)%.o
	$(LD) -shared -fPIC -o $@ $^

$(TARGETDIR)/lib$(LIBDEVICEDRIVER_TARGET).so: CFLAGS+=-fPIC
$(TARGETDIR)/lib$(LIBDEVICEDRIVER_TARGET).so: $(LIBDEVICEDRIVER_OBJS)
	$(LD) -shared -fPIC -o $@ $^

$(OBJDIR)/lib$(LIBDEVICEDRIVER_TARGET).a: $(LIBDEVICEDRIVER_OBJS)
	$(AR) rcs $@ $^

$(TARGETDIR)/$(MAIN_TARGET): $(MAIN_OBJS) | $(TARGETDIR)/lib$(LIB_TARGET).so $(TARGETDIR)/$(LIBDEVICEDRIVER)
	$(CC) $^ -o $@ -L$(TARGETDIR) -l$(LIB_TARGET) -ldl

static: $(MAIN_OBJS) $(OBJDIR)/lib$(LIB_TARGET).a $(OBJDIR)/lib$(LIBDEVICEDRIVER_TARGET).a
	$(CC) $^ -o $(TARGETDIR)/$(MAIN_TARGET)

clean: clean_libs
	$(RM) $(TARGETDIR)/$(MAIN_TARGET) $(MAIN_OBJS) $(TARGETDIR)/lib$(LIB_TARGET).so
	$(RM) -r $(OBJDIR) $(TARGETDIR)
	$(RM) $(KEYBOARDMAP) $(REMOTEMAP)

clean_libs:
	$(RM) $(TARGETDIR)/lib$(LIBDEVICEADAPTER_TARGET)*.so  $(LIBDEVICEADAPTER_OBJS)
	$(RM) $(TARGETDIR)/lib$(LIBDEVICEDRIVER_TARGET).so   $(LIBDEVICEDRIVER_OBJS)

ARCHIVERDIR=../../archiver/$(ARCH)xbinary

ifneq ($(origin PACKAGEDIR), undefined)
	$(PACKAGEDIR)+="/"
endif

$(PREFIX):
	$(MKDIR) -p $(PREFIX)

$(BINDIR):
	$(MKDIR) -p $(BINDIR)

$(LIBDIR):
	$(MKDIR) -p $(LIBDIR)

$(SHAREDIR):
	$(MKDIR) -p $(SHAREDIR)

$(CONFIGDIR):
	$(MKDIR) -p $(CONFIGDIR)

install: $(PREFIX) install-bin install-lib install-share install-config

install-bin:$(BINDIR)
	$(CP) $(TARGETDIR)/$(MAIN_TARGET) $(PACKAGEDIR)$(BINDIR)

install-lib:$(LIBDIR)
	$(CP) $(TARGETDIR)/lib$(LIB_TARGET).so $(PACKAGEDIR)$(LIBDIR)

install-share:$(SHAREDIR)
	$(CP)  $(TARGETDIR)/lib$(LIBDEVICEADAPTER_TARGET)*.so $(TARGETDIR)/lib$(LIBDEVICEDRIVER_TARGET).so $(TARGETDIR)/$(KEYBOARDMAP) $(PACKAGEDIR)$(SHAREDIR)

install-config:

