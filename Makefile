PREFIX = /usr/local

CC = gcc

all: pac

pac: main.c
	$(CC) main.c -o $@ $(CFLAGS)

clean:
	-rm -f pac

install: all
	install -Dm755 pac $(DESTDIR)$(PREFIX)/bin/pac

uninstall:
	-rm -f $(DESTDIR)$(PREFIX)/bin/pac

.PHONY: all install uninstall clean
