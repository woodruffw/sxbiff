CC = cc
CFLAGS = -std=c99 -O3
LDFLAGS = -lX11
CPPFLAGS = -D_POSIX_C_SOURCE=200112L
INSTALL = install -c

PREFIX = /usr/local
BIN = $(PREFIX)/bin
MAN = $(PREFIX)/share/man/man1

SOURCES = $(wildcard ./*.c)
OBJECTS = $(SOURCES:.c=.o)

PROG = sxbiff
MANPAGE = sxbiff.1

all: $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJECTS) -o $(PROG) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

install: all
	$(INSTALL) $(PROG) $(BIN)/$(PROG)
	mkdir -p $(MAN)
	$(INSTALL) $(MANPAGE) $(MAN)/$(MANPAGE)

clean:
	rm -f *.o $(PROG)

.PHONY: all clean
