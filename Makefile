PREFIX?=/usr/local
BINDIR?=$(PREFIX)/bin
LIBDIR?=$(PREFIX)/lib
CONFIGDIR?=$(PREFIX)/etc/anymote
SHAREDIR?=$(PREFIX)/share/anymote

export PREFIX
export BINDIR
export LIBDIR
export CONFIGDIR
export SHAREDIR

all:
	$(MAKE) -C src
	$(MAKE) -C tools

clean:
	$(MAKE) -C src clean
	$(MAKE) -C tools clean

install:
	$(MAKE) -C src install
	$(MAKE) -C tools install
