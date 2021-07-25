DESTDIR   ?=
PREFIX    ?= /usr/local
MANPREFIX ?= $(PREFIX)/man

CFLAGS += -Wall -Wextra

all: dated

clean:
	rm -f dated

install: dated
	install -d $(DESTDIR)$(PREFIX)/bin $(DESTDIR)$(MANPREFIX)/man1
	install -m755 dated $(DESTDIR)$(PREFIX)/bin/
	install -m644 dated.1 $(DESTDIR)$(MANPREFIX)/man1/

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/dated
	rm -f $(DESTDIR)$(MANPREFIX)/man1/dated.1

.PHONY: all clean install uninstall
