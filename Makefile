CC ?= gcc
CFLAGS ?= -Wall -Wextra -O3

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin

TARGET = ayasfetch

all: $(TARGET)

$(TARGET): ayasfetch.c
	$(CC) $(CFLAGS) -o $(TARGET) ayasfetch.c

install: $(TARGET)
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)/

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean install uninstall
