# Globals and files to compile.
SOURCEDIR := src

# User options.
PREFIX  = /usr
DESTDIR =

CC = gcc

CFLAGS = -O2 -pipe -Wall -Wextra

CHARDFLAGS := $(CFLAGS) -masm=intel -I$(SOURCEDIR)

.PHONY: all clean install uninstall

all:
	$(CC) $(CHARDFLAGS) $(SOURCEDIR)/util/messages.c $(SOURCEDIR)/mount.c  -o mount
	$(CC) $(CHARDFLAGS) $(SOURCEDIR)/util/sha256.c   $(SOURCEDIR)/cetty.c  -o cetty
	$(CC) $(CHARDFLAGS) $(SOURCEDIR)/cfetch.c -o cfetch
	$(CC) $(CHARDFLAGS) $(SOURCEDIR)/util/messages.c $(SOURCEDIR)/umount.c -o umount

clean:
	rm -f mount
	rm -f cetty
	rm -f cfetch
	rm -f umount

install:
	install -d $(DESTDIR)$(PREFIX)/bin
	install -s mount  $(DESTDIR)$(PREFIX)/bin
	install -s cetty  $(DESTDIR)$(PREFIX)/bin
	install -s cfetch $(DESTDIR)$(PREFIX)/bin
	install -s umount $(DESTDIR)$(PREFIX)/bin

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/mount
	rm -f $(DESTDIR)$(PREFIX)/bin/cetty
	rm -f $(DESTDIR)$(PREFIX)/bin/cfetch
	rm -f $(DESTDIR)$(PREFIX)/bin/umount
